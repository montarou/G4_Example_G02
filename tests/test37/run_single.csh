#/bin/csh

${2} ${3}Aluminum.in 
mv Sandia.out Al_${1}.log

${2} ${3}Molibdenum.in 
mv Sandia.out Mo_${1}.log

${2} ${3}Tantalum.in 
mv Sandia.out Ta_${1}.log

${2} ${3}TaAl.in 
mv Sandia.out TaAl_${1}.log

${2} ${3}AlAuAl.in 
mv Sandia.out AlAuAl_${1}.log

