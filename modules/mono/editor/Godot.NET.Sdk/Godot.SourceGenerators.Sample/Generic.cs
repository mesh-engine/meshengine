namespace Mesh.SourceGenerators.Sample
{
    partial class Generic<T> : Mesh.Object
    {
    }

    // Generic again but different generic parameters
    partial class Generic<T, R> : Mesh.Object
    {
    }

    // Generic again but without generic parameters
    partial class Generic : Mesh.Object
    {
    }
}
