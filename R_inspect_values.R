library(RCurl)

collect = data.frame()
while(TRUE){
  r <- getURL("https://api.relayr.io/devices/<DEVICE_ID>/readings", httpheader = c("content-type" = "application/json", "Authorization"='<TOKEN>','Cache-Control'='no-cache'))
  r <- fromJSON(r)                                                                                                    
  value <- r$readings$value
  print(value)
  dat <- as.data.frame(value)
  names(dat) <- "value"
  dat$time <- Sys.time()
  collect <- rbind(collect, dat)
}

hist(collect$value, 100,main = "Sound Values", xlab = "value")
