param([string]$buildType="Release")
$ErrorActionPreference = "Stop"
Set-StrictMode -Version 3.0

$projectRoot = Resolve-Path "$PSScriptRoot/.."

Set-Location $projectRoot
cmake -B build -S "$projectRoot" --preset ALL --fresh
cmake --build "$projectRoot/build" --config "$($buildType)"
Set-Location "$projectRoot/build"
cpack
Set-Location $projectRoot