#!/bin/bash

CONFIG_SRC_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo -e "\e[32mInstalling configuration from:$CONFIG_SRC_DIR\e[0m"

# --- Detect OS ---
detect_os() {
    case "$(uname -s)" in
        Darwin)
            echo "macos"
            ;;
        Linux)
            if [ -f /etc/os-release ]; then
                . /etc/os-release
                case "$ID" in
                    fedora|centos|rhel|rocky|alma)
                        echo "rhel"
                        ;;
                    ubuntu|debian|pop|mint|elementary)
                        echo "debian"
                        ;;
                    arch|manjaro)
                        echo "arch"
                        ;;
                    opensuse*|sles)
                        echo "suse"
                        ;;
                    *)
                        echo "unknown-linux"
                        ;;
                esac
            else
                echo "unknown-linux"
            fi
            ;;
        MINGW*|MSYS*|CYGWIN*)
            echo "windows"
            ;;
        *)
            echo "unknown"
            ;;
    esac
}

OS="$(detect_os)"
echo "Detected OS family: $OS"

# --- Pre-configure timezone for non-interactive Debian/Ubuntu installs ---
if [ "$OS" = "debian" ]; then
    export DEBIAN_FRONTEND=noninteractive
    export TZ="America/Los_Angeles"
    sudo ln -snf /usr/share/zoneinfo/"$TZ" /etc/localtime
    echo "$TZ" | sudo tee /etc/timezone > /dev/null
fi

# --- Fix hostname resolution for sudo (e.g. inside Docker containers) ---
if ! hostname -f &>/dev/null; then
    echo "127.0.0.1 $(hostname)" | sudo tee -a /etc/hosts > /dev/null
fi

# --- Package install helper ---
install_pkg() {
    local pkg_debian="$1"
    local pkg_rhel="$2"
    local pkg_macos="$3"
    local pkg_arch="$4"
    local pkg_suse="$5"

    case "$OS" in
        debian)
            sudo apt install -y "$pkg_debian"
            ;;
        rhel)
            if command -v dnf &>/dev/null; then
                sudo dnf install -y "$pkg_rhel"
            else
                sudo yum install -y "$pkg_rhel"
            fi
            ;;
        macos)
            brew install "$pkg_macos"
            ;;
        arch)
            sudo pacman -S --noconfirm "$pkg_arch"
            ;;
        suse)
            sudo zypper install -y "$pkg_suse"
            ;;
        windows)
            echo "Windows detected — install '$pkg_debian' manually or via chocolatey/scoop."
            ;;
        *)
            echo "Unknown OS — cannot install '$pkg_debian' automatically."
            ;;
    esac
}

# --- Copy dotfiles ---
if [ -z "$XDG_CONFIG_HOME" ]; then
    USER_CONFIG_DIR="$HOME/.config"
else
    USER_CONFIG_DIR="$XDG_CONFIG_HOME"
fi

mkdir -p "$USER_CONFIG_DIR"

cp -r "$CONFIG_SRC_DIR/.config/nvim" "$USER_CONFIG_DIR/"
NEOVIM_CONFIG_DIR=$USER_CONFIG_DIR/nvim
echo "Neovim config dir located at:$NEOVIM_CONFIG_DIR"

cp -r "$CONFIG_SRC_DIR/.vim" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.vimrc" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.coc.vim" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.fzf" "$HOME/"
cp -r "$CONFIG_SRC_DIR/.set-title.sh" "$HOME/"

# --- Source .set-title.sh in the user's shell rc ---
SHELL_RC="$HOME/.bashrc"
if [ -n "$ZSH_VERSION" ] || [ "$(basename "$SHELL")" = "zsh" ]; then
    SHELL_RC="$HOME/.zshrc"
fi

grep --quiet ".set-title.sh" "$SHELL_RC" 2>/dev/null ||
  echo "source $HOME/.set-title.sh" >> "$SHELL_RC"

# --- Install fzf ---
pushd ~/.fzf || exit
./install --all
popd

# --- Install packages ---
#                     debian                   rhel                      macos                  arch                   suse
install_pkg          "silversearcher-ag"       "the_silver_searcher"     "the_silver_searcher"  "the_silver_searcher"  "the_silver_searcher"
install_pkg          "curl"                    "curl"                    "curl"                 "curl"                 "curl"
install_pkg          "vim"                     "vim-enhanced"            "vim"                  "vim"                  "vim"

# --- Initialize git submodules (Vundle, etc.) ---
pushd "$CONFIG_SRC_DIR" || exit
git config --global --add safe.directory "$CONFIG_SRC_DIR"
git submodule update --init --recursive
popd

# --- Install Node.js (needed for coc.nvim) ---
if [ "$OS" = "macos" ]; then
    brew install node
    export PATH="${PATH}:/usr/local/bin/"
elif command -v node &>/dev/null; then
    echo "Node.js already installed: $(node --version)"
else
    curl -sL install-node.now.sh/lts | sudo bash -s -- --yes
fi

# --- Install Yarn (needed to build coc.nvim) ---
if command -v node &>/dev/null; then
    if [ "$OS" = "macos" ]; then
        npm install -g yarn
    else
        sudo npm install -g yarn
    fi
else
    echo "Warning: Node.js installation failed. Skipping yarn/coc.nvim setup."
    echo "Install Node.js manually and re-run the script."
fi

# --- Install Vim plugins ---
vim +PluginInstall +qall

if command -v yarn &>/dev/null && [ -d "$HOME/.vim/bundle/coc.nvim" ]; then
    pushd "$HOME/.vim/bundle/coc.nvim" || exit
    yarn install --frozen-lockfile
    popd
elif [ ! -d "$HOME/.vim/bundle/coc.nvim" ]; then
    echo "Warning: coc.nvim not found. Run :PluginInstall in Vim first."
fi

# --- Case-insensitive tab completion ---
echo "set completion-ignore-case On" > "$HOME/.inputrc"

echo ""
echo -e "\e[32mYour Vim configuration is complete.\e[0m"
echo "Refer to README for further instructions to set up language support."
