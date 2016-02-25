#libraries
library(raster)
library(RColorBrewer)

args <- commandArgs(trailingOnly=T)
matrixFile <- args[1]
outputList <- args[2]
outputRaster <- args[3]
#input data
m <- as.matrix(read.csv(matrixFile, header=T, sep = '\t', row.names = 1, as.is=T))
#reorder alphabetically
m.sorted <- m[order(row.names(m)), order(row.names(m))]

#cluster
m.tmp <- m.sorted
m.tmp[m.tmp=="NaN"] <- 0.0
m.tmp[m.tmp==NaN] <- 0.0
m.clust <- hclust(as.dist(1-m.tmp))
row.order <- m.clust$order
m.order <- m.sorted[row.order, row.order]

write(rownames(m.order), outputList)
#write.table(m.order, outputList, sep='\t', quote=F)

#make the raster
m.raster <- raster(m.order)

#make the color function
n=256
cols <- colorRampPalette(rev(brewer.pal(11,"RdBu")))(n)
breaks <- c(seq(-1, 0, length.out=n/2)-0.001, 0, seq(0, 1, length.out=n/2)+0.001)

#create the image
png(outputRaster, width=2000, height=2000)
plot(m.raster, col=cols, breaks=breaks, interpolate=FALSE, xlim=c(0,1), ylim=c(0,1), legend=FALSE, axes=FALSE, bty="n", box=FALSE)
plot(m.raster, legend.only=TRUE, col=cols, breaks=breaks, axis.args=list(at=seq(-1, 1, 1), labels=seq(-1, 1, 1)))
dev.off()
