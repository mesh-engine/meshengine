using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace Mesh.SourceGenerators
{
    public static class Common
    {
        public static void ReportNonPartialMeshScriptClass(
            GeneratorExecutionContext context,
            ClassDeclarationSyntax cds, INamedTypeSymbol symbol
        )
        {
            string message =
                "Missing partial modifier on declaration of type '" +
                $"{symbol.FullQualifiedName()}' which is a subclass of '{MeshClasses.Object}'";

            string description = $"{message}. Subclasses of '{MeshClasses.Object}' must be " +
                                 "declared with the partial modifier or annotated with the " +
                                 $"attribute '{MeshClasses.DisableMeshGeneratorsAttr}'.";

            context.ReportDiagnostic(Diagnostic.Create(
                new DiagnosticDescriptor(id: "MESH-G0001",
                    title: message,
                    messageFormat: message,
                    category: "Usage",
                    DiagnosticSeverity.Error,
                    isEnabledByDefault: true,
                    description),
                cds.GetLocation(),
                cds.SyntaxTree.FilePath));
        }
    }
}
