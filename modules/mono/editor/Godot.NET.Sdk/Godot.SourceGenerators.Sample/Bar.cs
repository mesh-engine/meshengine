namespace Mesh.SourceGenerators.Sample
{
    partial class Bar : Mesh.Object
    {
    }

    // Foo in another file
    partial class Foo
    {
    }

    partial class NotSameNameAsFile : Mesh.Object
    {
    }
}
