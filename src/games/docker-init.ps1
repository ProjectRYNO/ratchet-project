param (
    [switch]$rebuild,
    [switch]$delete,
    [switch]$help
)

$ErrorActionPreference = 'Stop'
$ImageName = "projectryno"

function Invoke-DockerChecked {
    & docker @args
    if ($LASTEXITCODE -ne 0) {
        throw "Docker failed with exit code $LASTEXITCODE."
    }
}

function Show-Usage {
    Write-Host "Usage: .\docker-init.ps1 [OPTION]"
    Write-Host ""
    Write-Host "  (no args)   Build image if it doesn't exist, then open a container shell"
    Write-Host "  -rebuild    Force a fresh image build, then open a container shell"
    Write-Host "  -delete     Remove all Project RYNO containers and image, then exit"
    Write-Host "  -help       Show this help message"
}

function Test-DockerAvailable {
    if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
        Write-Host "[Project RYNO] Error: 'docker' command not found."
        Write-Host "               Make sure Docker Desktop is installed and running, then try again."
        Write-Host "               https://www.docker.com/products/docker-desktop/"
        exit 1
    }
}

function Test-ImageExists {
    # A missing image is an expected nonzero result, including its stderr.
    $savedPreference = $ErrorActionPreference
    try {
        $ErrorActionPreference = 'Continue'
        docker image inspect $ImageName *> $null
        return $LASTEXITCODE -eq 0
    } finally {
        $ErrorActionPreference = $savedPreference
    }
}

if ($help) {
    Show-Usage
    exit 0
}
Test-DockerAvailable
Push-Location -LiteralPath $PSScriptRoot
try {
    if ($rebuild) {
        Write-Host "[Project RYNO] Rebuilding image..."
        Invoke-DockerChecked compose build --no-cache projectryno
        Invoke-DockerChecked compose run projectryno
    } elseif ($delete) {
        Write-Host "[Project RYNO] Removing Project RYNO containers..."
        $containers = docker ps -aq --filter "name=projectryno"
        if ($LASTEXITCODE -ne 0) { throw "Unable to list Docker containers." }
        if ($containers) {
            Invoke-DockerChecked rm -f $containers
            Write-Host "[Project RYNO] Containers removed."
        } else {
            Write-Host "[Project RYNO] No containers found."
        }

        if (Test-ImageExists) {
            Write-Host "[Project RYNO] Deleting image '$ImageName'..."
            Invoke-DockerChecked image rm -f $ImageName
            Write-Host "[Project RYNO] Done."
        } else {
            Write-Host "[Project RYNO] Image '$ImageName' not found, nothing to delete."
        }
    } else {
        if (-not (Test-ImageExists)) {
            Write-Host "[Project RYNO] Image not found, building..."
            Invoke-DockerChecked compose build projectryno
        } else {
            Write-Host "[Project RYNO] Image already exists, skipping build."
        }
        Invoke-DockerChecked compose run projectryno
    }
} finally {
    Pop-Location
}
