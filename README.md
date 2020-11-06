# My Space

The repository contains shared config for vim and neovim.

If you build NVIM from source, do this:
```
sudo update-alternatives --install /usr/bin/vi vi /usr/bin/nvim 60
sudo update-alternatives --config vi
sudo update-alternatives --install /usr/bin/vim vim /usr/bin/nvim 60
sudo update-alternatives --config vim
sudo update-alternatives --install /usr/bin/editor editor /usr/bin/nvim 60
sudo update-alternatives --config editor
```

Run the `install.sh` script first.

Start the Vim and do `:PluginInstall`.

Run the `build_coc.sh` script, this will install the dependencies and
build the coc.nvim plugin.

For each language server you want to use, install the coc plugin for it 
inside Vim
(e.g. `:CocInstall coc-clangd`   #C/C++
      `:CocInstall coc-go`       #Go
      `:CocInstall coc-rls`      #Rust
)

