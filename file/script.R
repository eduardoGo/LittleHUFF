#setwd("~/Área de Trabalho/LittleHUFF/file")
Dados <- read.table("file", header = FALSE)
plot(Dados[,1],Dados[,2], xlab = "QUANTIDADE DE ELEMENTOS",ylab = "COMPARAÇÕES", type = "l", col = 2)
lines(Dados[,3], col = 3)

