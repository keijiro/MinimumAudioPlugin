Minimum Audio Plugin
====================

![fig](https://i.imgur.com/J03Bjn1.png)

This is an example that shows a minimum implementation of a [native audio
plugin] for Unity.

Although this example might be helpful to grasp the basic idea of Unity's
native audio plugin, it doesn't deep dive into further topics. For more
detailed examples, please check [the official examples repository] available
on BitBucket.

[native audio plugin]: https://docs.unity3d.com/Manual/AudioMixerNativeAudioPlugin.html
[the official examples repository]: https://bitbucket.org/Unity-Technologies/nativeaudioplugins

What This Plugin Does
---------------------

Just generating and sending a sine wave signal to the destination port.

Common Pitfalls
---------------

Although implementing a native audio plugin is pretty straightforward, there is
one common pitfall that should be aware of.

> ... the current convention is to prefix the DLL of the plugin “audioplugin”
> (case insensitive) so that the system can detect this and add it to a list
> of plugins that will automatically be loaded at start. 

So, if you can't find your plugin in the audio effect drop-down list, please
check if the filename of the plugin is following this convention.

License
-------

[Public domain](https://unlicense.org)
