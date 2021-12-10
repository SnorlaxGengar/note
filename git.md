## 从HTTPS转成SSH

`git remote set-url origin git@github.com:SnorlaxGengar/note.git`

## 设置代理

`git config --global http.proxy 'socks5://127.0.0.1:1080'`

## 设置编辑器

`git config --global core.editor vim`

## 添加密钥后测试服务器

`ssh -T git@github.com`