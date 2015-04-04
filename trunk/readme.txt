gedit ~/.bashrc
source ~/.bashrc
sudo su
sudo -i

#Project Lawliet
PRJ=/home/lawliet/Lawliet/trunk
PATH=$PATH:$PRJ
export PATH PRJ

echo "-----------------------------------------"
echo "#Project Lawliet                         "
echo "PRJ = /home/lawliet/Lawliet/trunk        "
echo "@2015/03/07                              "
echo "-----------------------------------------"

--------------------------------------------------------------------------------------------------------

#if we can't edit the file
gksudo gedit filename

chown lawliet:lawliet *

#./lawliet: error while loading shared libraries: libutility.so: cannot open 
shared object file: No such file or directory

>> ldd lawliet
>> echo "/home/lawliet/Lawliet/trunk/src/app/libs" >> /etc/ld.so.conf
>> ldconfig

--------------------------------------------------------------------------------------------------------

#git skill

workspace / stage(index) / local repository / remote repository
git ls-files
git log --pretty=oneline
git diff                 => workspace vs stage
git diff --cached HEAD   => stage     vs HEAD
git diff --cached        => stage     vs HEAD
git diff HEAD            => workspace vs HEAD
git diff HEAD^ HEAD      => HEAD^     vs HEAD

git clone https://github.com/lawlietshih/Lawliet.git

git tag
git branch
git log -1 (git commit)
git shortlog

git rm 
git mv
git add *
git add .
git reset HEAD trunk/src/app/main.o

git diff HEAD
git status -s
git status
# On branch master
nothing to commit (working directory clean)

git checkout trunk/src/app/Makefile
git checkout HEAD

git pull origin master
From https://github.com/lawlietshih/Lawliet
 * branch            master     -> FETCH_HEAD
Already up-to-date.
git config --global user.email "prjlawliet@gmail.com" 
git config --global user.name "lawlietshih"
git commit -am "commit msg"
git reset --hard HEAD
git reset --hard ORIG_HEAD
git reset --soft "HEAD^"

git push -u origin master = git fetch + git merge origin/master
Username for 'https://github.com': lawlietshih         
Password for 'https://lawlietshih@github.com':

--------------------------------------------------------------------------------------------------------

git config --global alias.co   checkout
git config --global alias.ci   commit
git config --global alias.st   status
git config --global alias.sts  "status -s"
git config --global alias.br   branch
git config --global alias.re   remote
git config --global alias.di   diff
git config --global alias.type "cat-file -t"
git config --global alias.dump "cat-file -p"
git config --global alias.lo   "log --oneline"
git config --global alias.ll "log --pretty=format:'%h %ad | %s%d [%Cgreen%an%Creset]' --graph --date=short"
git config --global alias.lg "log --graph --pretty=format:'%Cred%h%Creset %ad |%C(yellow)%d%Creset %s %Cgreen(%cr)%Creset [%Cgreen%an%Creset]' --abbrev-commit --date=short"

--------------------------------------------------------------------------------------------------------

#svn skill

svn export
svn co

svn info

svn mv
svn add
svn delete (del, remove, rm)

svn up
svn diff > 2012110801.txt 
svn st | grep ^[^?]
svn ci -m "commit msg"

--------------------------------------------------------------------------------------------------------

#gcc

#shared library (.so)

#static library (.a)

--------------------------------------------------------------------------------------------------------

#Makefile


