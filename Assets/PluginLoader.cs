using UnityEngine;
using System.Runtime.InteropServices;

public class PluginLoader : MonoBehaviour
{
    [DllImport("SinOsc")]
    static extern bool InitPlugin();

    void Start()
    {
        Debug.Log("InitPlugin: " + InitPlugin());
    }
}
