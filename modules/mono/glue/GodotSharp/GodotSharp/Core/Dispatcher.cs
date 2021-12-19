using System.Runtime.CompilerServices;

namespace Mesh
{
    public static class Dispatcher
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern MeshTaskScheduler mesh_icall_DefaultMeshTaskScheduler();

        public static MeshSynchronizationContext SynchronizationContext =>
            mesh_icall_DefaultMeshTaskScheduler().Context;
    }
}
