# Build Mesh.NET.Sdk solution

import os

from SCons.Script import Dir


def build_mesh_net_sdk(source, target, env):
    # source and target elements are of type SCons.Node.FS.File, hence why we convert them to str

    module_dir = env["module_dir"]

    solution_path = os.path.join(module_dir, "editor/Mesh.NET.Sdk/Mesh.NET.Sdk.sln")
    build_config = "Release"

    from .solution_builder import build_solution

    extra_msbuild_args = ["/p:MeshPlatform=" + env["platform"]]

    build_solution(env, solution_path, build_config, extra_msbuild_args)
    # No need to copy targets. The Mesh.NET.Sdk csproj takes care of copying them.


def get_nupkgs_versions(props_file):
    import xml.etree.ElementTree as ET

    tree = ET.parse(props_file)
    root = tree.getroot()

    return {
        "Mesh.NET.Sdk": root.find("./PropertyGroup/PackageVersion_Mesh_NET_Sdk").text.strip(),
        "Mesh.SourceGenerators": root.find("./PropertyGroup/PackageVersion_Mesh_SourceGenerators").text.strip(),
    }


def build(env_mono):
    assert env_mono["tools"]

    output_dir = Dir("#bin").abspath
    editor_tools_dir = os.path.join(output_dir, "MeshSharp", "Tools")
    nupkgs_dir = os.path.join(editor_tools_dir, "nupkgs")

    module_dir = os.getcwd()

    nupkgs_versions = get_nupkgs_versions(os.path.join(module_dir, "SdkPackageVersions.props"))

    target_filenames = [
        "Mesh.NET.Sdk.%s.nupkg" % nupkgs_versions["Mesh.NET.Sdk"],
        "Mesh.SourceGenerators.%s.nupkg" % nupkgs_versions["Mesh.SourceGenerators"],
    ]

    targets = [os.path.join(nupkgs_dir, filename) for filename in target_filenames]

    cmd = env_mono.CommandNoCache(targets, [], build_mesh_net_sdk, module_dir=module_dir)
    env_mono.AlwaysBuild(cmd)
