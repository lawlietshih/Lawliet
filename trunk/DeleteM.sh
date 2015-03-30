touch love_tmp
#sed 's/^M//' $1 > love_tmp
cat $1 | tr -d '\r' > love_tmp
mv love_tmp $1
