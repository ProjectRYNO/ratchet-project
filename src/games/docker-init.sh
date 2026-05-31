#!/bin/bash

IMAGE_NAME="rc1-decomp"

usage() {
    echo "Usage: bash docker-init.sh [OPTION]"
    echo ""
    echo "  (no args)   Build image if it doesn't exist, then open a container shell"
    echo "  --rebuild   Force a fresh image build, then open a container shell"
    echo "  --delete    Remove the image and exit"
    echo "  --help      Show this help message"
}

case "$1" in
    --rebuild)
        echo "[rc1] Rebuilding image..."
        docker build --no-cache -t "$IMAGE_NAME" .
        docker compose run rc1
        ;;
    --delete)
        if docker image inspect "$IMAGE_NAME" > /dev/null 2>&1; then
            echo "[rc1] Deleting image '$IMAGE_NAME'..."
            docker image rm "$IMAGE_NAME"
            echo "[rc1] Done."
        else
            echo "[rc1] Image '$IMAGE_NAME' not found, nothing to delete."
        fi
        ;;
    --help)
        usage
        ;;
    "")
        if ! docker image inspect "$IMAGE_NAME" > /dev/null 2>&1; then
            echo "[rc1] Image not found, building..."
            docker build -t "$IMAGE_NAME" .
        else
            echo "[rc1] Image already exists, skipping build."
        fi
        docker compose run rc1
        ;;
    *)
        echo "[rc1] Unknown argument: $1"
        usage
        exit 1
        ;;
esac