using System;
using System.Runtime.CompilerServices;

namespace Mesh
{
    public partial class Object : IDisposable
    {
        private bool _disposed = false;

        private static StringName nativeName = "Object";

        internal IntPtr ptr;
        internal bool memoryOwn;

        /// <summary>
        /// Constructs a new <see cref="Object"/>.
        /// </summary>
        public Object() : this(false)
        {
            if (ptr == IntPtr.Zero)
                ptr = mesh_icall_Object_Ctor(this);
            _InitializeMeshScriptInstanceInternals();
        }

        internal void _InitializeMeshScriptInstanceInternals()
        {
            mesh_icall_Object_ConnectEventSignals(ptr);
        }

        internal Object(bool memoryOwn)
        {
            this.memoryOwn = memoryOwn;
        }

        /// <summary>
        /// The pointer to the native instance of this <see cref="Object"/>.
        /// </summary>
        public IntPtr NativeInstance
        {
            get { return ptr; }
        }

        internal static IntPtr GetPtr(Object instance)
        {
            if (instance == null)
                return IntPtr.Zero;

            if (instance._disposed)
                throw new ObjectDisposedException(instance.GetType().FullName);

            return instance.ptr;
        }

        ~Object()
        {
            Dispose(false);
        }

        /// <summary>
        /// Disposes of this <see cref="Object"/>.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Disposes implementation of this <see cref="Object"/>.
        /// </summary>
        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
                return;

            if (ptr != IntPtr.Zero)
            {
                if (memoryOwn)
                {
                    memoryOwn = false;
                    mesh_icall_RefCounted_Disposed(this, ptr, !disposing);
                }
                else
                {
                    mesh_icall_Object_Disposed(this, ptr);
                }

                ptr = IntPtr.Zero;
            }

            _disposed = true;
        }

        /// <summary>
        /// Converts this <see cref="Object"/> to a string.
        /// </summary>
        /// <returns>A string representation of this object.</returns>
        public override string ToString()
        {
            return mesh_icall_Object_ToString(GetPtr(this));
        }

        /// <summary>
        /// Returns a new <see cref="SignalAwaiter"/> awaiter configured to complete when the instance
        /// <paramref name="source"/> emits the signal specified by the <paramref name="signal"/> parameter.
        /// </summary>
        /// <param name="source">
        /// The instance the awaiter will be listening to.
        /// </param>
        /// <param name="signal">
        /// The signal the awaiter will be waiting for.
        /// </param>
        /// <example>
        /// This sample prints a message once every frame up to 100 times.
        /// <code>
        /// public override void _Ready()
        /// {
        ///     for (int i = 0; i &lt; 100; i++)
        ///     {
        ///         await ToSignal(GetTree(), "process_frame");
        ///         GD.Print($"Frame {i}");
        ///     }
        /// }
        /// </code>
        /// </example>
        /// <returns>
        /// A <see cref="SignalAwaiter"/> that completes when
        /// <paramref name="source"/> emits the <paramref name="signal"/>.
        /// </returns>
        public SignalAwaiter ToSignal(Object source, StringName signal)
        {
            return new SignalAwaiter(source, signal, this);
        }

        /// <summary>
        /// Gets a new <see cref="DynamicMeshObject"/> associated with this instance.
        /// </summary>
        public dynamic DynamicObject => new DynamicMeshObject(this);

        internal static IntPtr __ClassDB_get_method(StringName type, string method)
        {
            return mesh_icall_Object_ClassDB_get_method(StringName.GetPtr(type), method);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern IntPtr mesh_icall_Object_Ctor(Object obj);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void mesh_icall_Object_Disposed(Object obj, IntPtr ptr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void mesh_icall_RefCounted_Disposed(Object obj, IntPtr ptr, bool isFinalizer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void mesh_icall_Object_ConnectEventSignals(IntPtr obj);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern string mesh_icall_Object_ToString(IntPtr ptr);

        // Used by the generated API
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern IntPtr mesh_icall_Object_ClassDB_get_method(IntPtr type, string method);
    }
}
