using System;

namespace Mesh
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]
    public class ScriptPathAttribute : Attribute
    {
        private string path;

        public ScriptPathAttribute(string path)
        {
            this.path = path;
        }
    }
}
