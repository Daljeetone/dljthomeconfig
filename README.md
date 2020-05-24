# My Space

The repository contains shared config for vim and neovim.

Run the "install.sh" script first.

If you do not want to use coc.nvim (Language Server Plugin),
then remove the coc.nvim plugin from your .vimrc file now.

Start the Vim and do ":PluginInstall".

If you have chosen to keep coc.nvim Plugin, run the "build\_coc.sh" script
after running :PluginInstall, this will install the dependencies and
build the coc.nvim plugin.

For each language server you want to use:
Install the language server (e.g. sudo apt install clangd) and then
install the coc plugin for it inside Vim (e.g. :CocInstall coc-clangd)

