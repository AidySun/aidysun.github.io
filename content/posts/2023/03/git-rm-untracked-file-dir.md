---
title: '如何删除本地 git 中未追踪的文件/文件夹'
description: 'git clean'
date: 2023-03-20
author: 'SZH'
tags: ["Git", "Development", "2023", "2023-03"]
---

对于一个 git 项目，执行 `git status -u` 有如下状态：

![git status -u result](/images/git-status--u.png "hi")

对于本地新增的文件，可以通过 `clean` 命令直接删除：

![git clean -f](/images/git-clean--f.png)

![after clean](/images/git-status--u-2.png)

但是本地新增的文件夹却没有被删除掉。要删除文件夹需要加上 `-d` 参数：

![git clean -f -d](/images/git-clean-fd.png)

还有一种情况就是已经在 `.gitignore` 中的文件或文件夹是不会被删除的。

![cat .gitignore](/images/cat-.gitignore.png)

![git status --ignored](/images/git-status---ignored.png)

需要通过 `-x` 选项来删除被 `.gitignore` 包含的文件或文件夹：

![git clean -f -d -x](/images/git-clean--fdx.png)


## `git clean` options

|Option|Comments|
|:--:|--|
| `-f` | *Delete files or diretories* |
| `-d` | *Recurse into untracked directories* |
| `-x` | *Don’t use the standard ignore rules* |
