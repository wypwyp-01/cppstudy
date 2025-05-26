







##### 查看基本配置

```
wyp@wyp-VMware-Virtual-Platform:/home/study$ git config --list
user.name=wyp
user.email=1824226536@qq.com
```

![image-20250526172246654](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250526172246654.png)



![image-20250526172319371](C:\Users\wangyupeng\AppData\Roaming\Typora\typora-user-images\image-20250526172319371.png)

```
git init：在本目录下创建一个空的git仓库

git status:查看状态

git log  :查看提交历史
--all 显示所有分支
--pretty=oneline 将提交信息显示为一行
--abbrev-commit 使得输出的commitId更简短
--graph 以图的形式显示
```

git add命令:放进暂存区

| 命令            | 作用                                             |
| --------------- | ------------------------------------------------ |
| `git add .`     | 添加当前目录及其子目录下的所有文件               |
| `git add -A`    | 添加所有变动（包括删除的文件）                   |
| `git add *`     | 添加当前目录下的文件（**不含隐藏文件**和子目录） |
| `git add --all` | 和 `git add -A` 等价                             |



git commit -m "第一次添加文件"    :提交到本地仓库



git reset版本回退三种模式

| 模式              | HEAD（指针） | 暂存区（index） | 工作区（working dir） | 场景举例                                 |
| ----------------- | ------------ | --------------- | --------------------- | ---------------------------------------- |
| `--soft`          | ✅ 修改       | ❌ 保留          | ❌ 保留                | 撤销提交但保留改动                       |
| `--mixed`（默认） | ✅ 修改       | ✅ 重置          | ❌ 保留                | 撤销提交和暂存，保留文件改动             |
| `--hard`          | ✅ 修改       | ✅ 重置          | ✅ 清除                | 全部回退到某个提交，彻底抹掉改动（危险） |

git reflog ：查看改动的历史

.gitignore文件：暂时不想被跟踪的文件





##### git分支常用指令































