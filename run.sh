OS=$(uname)

# echo "Running on: "$OS" OS"

if [ "$OS" = "Darwin" ]; then
    EXEC_PATH="bin/Darwin/"
elif [ "$OS" = "Linux" ]; then
    EXEC_PATH="bin/Linux/"
else
    echo "Unsupported OS: $OS"
    exit 1
fi

./$EXEC_PATH/black_hole