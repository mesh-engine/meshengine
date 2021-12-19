namespace MeshTools
{
    public enum ExternalEditorId : long
    {
        None,
        VisualStudio, // TODO (Windows-only)
        VisualStudioForMac, // Mac-only
        MonoDevelop,
        VsCode,
        Rider
    }
}
