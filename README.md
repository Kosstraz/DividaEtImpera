# OPTIONS
**--divida** : Divide a file passed as parameter (not compatible with other options).<br/>
**--impera** : Reunite the sequence corresponding to the file param passed (only one file, is useless to pass all file sequence) (not compatible with divida).<br/>
**--in-bytes X** : Divide the file passed as parameter in several parts, each X bytes long (no compatible with --impera and --in-part).<br/>
**--in-parts N** : Divie the file passed as parameter in N parts (not compatible with --impera and --in-parts).<br/>
<br/>
**-d** corresponding to --divida<br/>
**-i** corresponding to --impera<br/>
**-b** corresponding to --in-bytes<br/>
**-p** corresponding to --in-parts<br/>

# USAGE
_Exemple 1:_ <br/>
./DividaEtImpera -db 1000000 small_image.png  ## separate the file in different file of each 1Mbytes long.<br/>
./DividaEtImpera -i small_image.pngN.dei      ## here the N is any part of the sequence.<br/>
<br/>
_Exemple 2:_ <br/>
./DividaEtImpera -dp 5 big_file.tgz.rar      ## separate the file in 5 files.<br/>
./DividaEtImpera -i big_file.tgz.rarN.dei    ## here the N is any part of the sequence.<br/>

# INFO
The name of the file should not be greater than 26 (or 27/28 if there is many parts).<br/>
Max parts possible is 254.
