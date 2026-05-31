#!/bin/bash

IMAGE_NAME="projectryno"

show_usage() {
    echo "Usage: ./docker-init.sh [OPTION]"
    echo ""
    echo "  (no args)   Build image if it doesn't exist, then open a container shell"
    echo "  --rebuild   Force a fresh image build, then open a container shell"
    echo "  --delete    Remove the image and exit"
    echo "  --help      Show this help message"
}

test_docker_available() {
    if ! command -v docker > /dev/null 2>&1; then
        echo "[Project RYNO] Error: 'docker' command not found."
        echo "               Make sure Docker Desktop is installed and running, then try again."
        echo "               https://www.docker.com/products/docker-desktop/"
        exit 1
    fi
}

test_image_exists() {
    docker image inspect "$IMAGE_NAME" > /dev/null 2>&1
}

test_docker_available

case "$1" in
    --rebuild)
        echo "[Project RYNO] Rebuilding image..."
        docker build --no-cache -t "$IMAGE_NAME" .
        docker compose run projectryno
        ;;
    --delete)
        if test_image_exists; then
            echo "[Project RYNO] Deleting image '$IMAGE_NAME'..."
            docker image rm "$IMAGE_NAME"
            echo "[Project RYNO] Done."
        else
            echo "[Project RYNO] Image '$IMAGE_NAME' not found, nothing to delete."
        fi
        ;;
    --help)
        show_usage
        ;;
    "")
        if ! test_image_exists; then
            echo "[Project RYNO] Image not found, building..."
            docker build -t "$IMAGE_NAME" .
        else
            echo "[Project RYNO] Image already exists, skipping build."
        fi
        docker compose run projectryno
        ;;
    *)
        echo "[Project RYNO] Unknown argument: $1"
        show_usage
        exit 1
        ;;
esac