## [安装zsh](https://wiki.archlinux.org/title/zsh#Installation)

`sudo pacman -S zsh-completions`

## [安装oh-my-zsh](https://ohmyz.sh/#install)

`sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"`

> curl: (7) Failed to connect to raw.githubusercontent.com port 443 after 28 ms: Connection refused

`sh -c "$(wget https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"`