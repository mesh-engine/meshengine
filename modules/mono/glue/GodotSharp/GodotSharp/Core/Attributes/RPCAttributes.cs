using System;

namespace Mesh
{
    [AttributeUsage(AttributeTargets.Method)]
    public class AnyPeerAttribute : Attribute { }

    [AttributeUsage(AttributeTargets.Method)]
    public class AuthorityAttribute : Attribute { }
}
