<#
Build Deadlocked and package its configured boot ELF using the project Docker image.
Run from any host directory. Rebuild the image after changing ratchet-ps2-cli.
#>
[CmdletBinding()]
param(
    [string]$Config,
    [switch]$SkipCompile
)
$ErrorActionPreference = 'Stop'
$gamesDirectory = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
if (-not $Config) { $Config = Join-Path $gamesDirectory 'assets/dl/config.ini' }
$configPath = (Resolve-Path -LiteralPath $Config).Path
$prefix = $gamesDirectory.TrimEnd('\') + '\'
if (-not $configPath.StartsWith($prefix, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Configuration must be inside src/games so it is available in the container.'
}
$containerConfig = '/ProjectRYNO/' + $configPath.Substring($prefix.Length).Replace('\', '/')
Push-Location -LiteralPath $gamesDirectory
try {
    if ($SkipCompile) {
        & docker compose run --rm --no-deps projectryno ratchet-ps2 map build-boot --config $containerConfig
    } else {
        # Run only after initial ROM/split setup, without another build in this tree.
        & docker compose run --rm --no-deps projectryno make -C /ProjectRYNO/dl -j8 iso "CLI_CONFIG=$containerConfig"
    }
    if ($LASTEXITCODE -ne 0) { throw 'Deadlocked build/pack failed; inspect the preceding diagnostic.' }
} finally {
    Pop-Location
}
