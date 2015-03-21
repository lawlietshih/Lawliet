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

--------------------------------------------------------------------------------------------------------------------------------

#if we can't edit the file
gksudo gedit filename

--------------------------------------------------------------------------------------------------------------------------------

#git skill

--------------------------------------------------------------------------------------------------------------------------------

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

