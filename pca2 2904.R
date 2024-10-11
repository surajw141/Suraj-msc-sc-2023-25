#car data
data(mtcars) #accessing mtcar data
?mtcars
head(mtcars, 5) #printing first 5 rows of data
n=nrow(mtcars) #no of objects
p=ncol(mtcars) #no of variables
#preparing data matrix
x=c()
for(i in 1:p)
  (
x=c(x,mtcars[,i])
)# mean standser
x
dm=matrix(x,nrow=n, ncol=p, byrow = FALSE)
#normalizing data
sdm=matrix(nrow = n, ncol = p)
for(i in 1:p)
{
  sdm[,i]=(dm[,i]-mean(dm[,i]))/sdm
}
mean(sdm[,1])
var(sdm)
round(cor(sdm),2)
#k means clustering for k= 3
?kmeans
k=3
km=kmeans(sdm, centers = k, nstart = 32)
km$cluster
km$size
#calculating between
tss=c()
for(i in 1:(n-2))
{temp=kmeans(sdm, centers=i+1, nstart = 32)
tss[i]=temp$tot, withinss
}
tsslenth(tss)
plot(
  ?
)
tee

var(sdm[,i])


?hclust


