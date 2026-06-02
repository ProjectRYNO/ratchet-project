param (
    [switch]$rebuild,
    [switch]$delete,
    [switch]$help
)

$ImageName = "projectryno"

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
    docker image inspect $ImageName 2>&1 | Out-Null
    return $LASTEXITCODE -eq 0
}

Test-DockerAvailable

if ($help) {
    Show-Usage
} elseif ($rebuild) {
    Write-Host "[Project RYNO] Rebuilding image..."
    docker build --no-cache -t $ImageName .
    docker compose run projectryno
} elseif ($delete) {
    Write-Host "[Project RYNO] Removing Project RYNO containers..."
    $containers = docker ps -aq --filter "name=projectryno"
    if ($containers) {
        docker rm -f $containers
        Write-Host "[Project RYNO] Containers removed."
    } else {
        Write-Host "[Project RYNO] No containers found."
    }

    if (Test-ImageExists) {
        Write-Host "[Project RYNO] Deleting image '$ImageName'..."
        docker image rm -f $ImageName
        Write-Host "[Project RYNO] Done."
    } else {
        Write-Host "[Project RYNO] Image '$ImageName' not found, nothing to delete."
    }
} else {
    if (-not (Test-ImageExists)) {
        Write-Host "[Project RYNO] Image not found, building..."
        docker build -t $ImageName .
    } else {
        Write-Host "[Project RYNO] Image already exists, skipping build."
    }
    docker compose run projectryno
}