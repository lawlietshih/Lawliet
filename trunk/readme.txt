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

git log -1

git rm 
git mv
git add *
git add .
git reset HEAD trunk/src/app/main.o

git diff HEAD
git status

git pull origin master
git config --global user.email "prjlawliet@gmail.com" 
git config --global user.name "lawlietshih"
git commit -am "commit msg"

git push -u origin master
Username for 'https://github.com': lawlietshih         
Password for 'https://lawlietshih@github.com': "

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

