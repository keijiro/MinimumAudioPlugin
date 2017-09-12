#include "AudioPluginInterface.h"
#include <cmath>
#include <cstring>

namespace
{
    struct EffectData
    {
        float frequency;
        float amplitude;
        float time;
    };

    UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK CreateCallback(
        UnityAudioEffectState* state
    )
    {
        auto* data = new EffectData();
        data->time = 0;
        state->effectdata = data;
        return UNITY_AUDIODSP_OK;
    }

    UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ReleaseCallback(
        UnityAudioEffectState* state
    )
    {
        delete state->GetEffectData<EffectData>();
        return UNITY_AUDIODSP_OK;
    }

    UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK ProcessCallback(
        UnityAudioEffectState* state, float* inBuffer, float* outBuffer,
        unsigned int length, int inChannels, int outChannels
    )
    {
        auto* data = state->GetEffectData<EffectData>();

        auto t = data->time;
        auto dt = data->frequency * 2 * 3.141592f / state->samplerate;
        auto offs = 0u;
        auto amp = powf(10, data->amplitude / 10);

        for (unsigned int i = 0; i < length; i++)
        {
            auto v = sinf(t) * amp;
            t += dt;

            for (int ch = 0; ch < outChannels; ch++)
                outBuffer[offs++] = v;
        }

        data->time = t;

        return UNITY_AUDIODSP_OK;
    }

    UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK SetFloatParameterCallback(
        UnityAudioEffectState* state, int index, float value
    )
    {
        auto* data = state->GetEffectData<EffectData>();

        switch (index)
        {
            case 0: data->frequency = value; break;
            case 1: data->amplitude = value; break;
            default: return UNITY_AUDIODSP_ERR_UNSUPPORTED;
        }

        return UNITY_AUDIODSP_OK;
    }

    UNITY_AUDIODSP_RESULT UNITY_AUDIODSP_CALLBACK GetFloatParameterCallback(
        UnityAudioEffectState* state,
        int index, float* value, char *valuestr
    )
    {
        auto* data = state->GetEffectData<EffectData>();

        float temp;
        switch (index)
        {
            case 0: temp = data->frequency; break;
            case 1: temp = data->amplitude; break;
            default: return UNITY_AUDIODSP_ERR_UNSUPPORTED;
        }

        if (value != nullptr) *value = temp;
        if (valuestr != nullptr) valuestr[0] = 0;

        return UNITY_AUDIODSP_OK;
    }

    UnityAudioEffectDefinition s_effectDefinition;
    UnityAudioEffectDefinition* s_effectList[] = { &s_effectDefinition };
    UnityAudioParameterDefinition s_parameters[2];

    void InitEffectDefinition()
    {
        auto& p1 = s_parameters[0];

        strncpy(p1.name, "Frequency", sizeof(p1.name));
        strncpy(p1.unit, "Hz", sizeof(p1.unit));
        p1.description = "Frequency of oscillation.";
        p1.min = 1;
        p1.max = 10000;
        p1.defaultval = 440;
        p1.displayscale = 1;
        p1.displayexponent = 2;

        auto& p2 = s_parameters[1];

        strncpy(p2.name, "Amplitude", sizeof(p2.name));
        strncpy(p2.unit, "dB", sizeof(p2.unit));
        p2.description = "Amplitude of output signal.";
        p2.min = -300;
        p2.max = 0;
        p2.defaultval = -8;
        p2.displayscale = 1;
        p2.displayexponent = 1;

        auto& def = s_effectDefinition;

        def.structsize = sizeof(UnityAudioEffectDefinition);
        def.paramstructsize = sizeof(UnityAudioParameterDefinition);
        def.apiversion = UNITY_AUDIO_PLUGIN_API_VERSION;

        strncpy(def.name, "Sine Oscillator", sizeof(def.name));
        def.pluginversion = 0x010000;
        def.channels = 1;
        def.numparameters = 2;
        def.paramdefs = s_parameters;

        def.create = CreateCallback;
        def.release = ReleaseCallback;
        def.process = ProcessCallback;
        def.setfloatparameter = SetFloatParameterCallback;
        def.getfloatparameter = GetFloatParameterCallback;
    }
}

extern "C" UNITY_AUDIODSP_EXPORT_API int UnityGetAudioEffectDefinitions(
    UnityAudioEffectDefinition*** definitionptr
)
{
    InitEffectDefinition();
    *definitionptr = s_effectList;
    return 1;
}
