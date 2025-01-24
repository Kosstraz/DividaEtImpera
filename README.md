# OPTIONS
--divida : Divide a file passed as parameter (not compatible with other options).
--impera : Reunite the sequence corresponding to the file param passed (only one file, is useless to pass all file sequence) (not compatible with divida).
--in-bytes X : Divide the file passed as parameter in several parts, each X bytes long (no compatible with --impera and --in-part).
--in-parts N : Divie the file passed as parameter in N parts (not compatible with --impera and --in-parts).

-d corresponding to --divida
-i corresponding to --impera
-b corresponding to --in-bytes
-p corresponding to --in-parts

# USAGE
_Exemple 1:_\n
./DividaEtImpera -db 1000000 small_image.png  ## separate the file in different file of each 1Mbytes long.\n
./DividaEtImpera -i small_image.pngN.dei      ## here the N is any part of the sequence.\n
\n
_Exemple 2:_\n
./DividaEtImpera -dp 5 big_file.tgz.rar      ## separate the file in 5 files.\n
./DividaEtImpera -i big_file.tgz.rarN.dei    ## here the N is any part of the sequence.\n

# INFO
The name of the file should not be greater than 26 (or 27/28 if there is many parts).\n
Max parts possible is 254.
