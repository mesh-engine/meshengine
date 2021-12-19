using System;

namespace Mesh
{
    [AttributeUsage(AttributeTargets.Delegate | AttributeTargets.Event)]
    public class SignalAttribute : Attribute { }
}
