using System;

namespace Mesh
{
    [AttributeUsage(AttributeTargets.Method)]
    internal class MeshMethodAttribute : Attribute
    {
        private string methodName;

        public string MethodName { get { return methodName; } }

        public MeshMethodAttribute(string methodName)
        {
            this.methodName = methodName;
        }
    }
}
