library(gtfsr)

gtfs <- import_gtfs("db_fv_google_transit_shp.zip", local=TRUE)
#gtfs <- import_gtfs("1190951.zip", local=TRUE)

trips_df <- gtfs$trips_df
stops_times_df <- gtfs$stop_times_df
stops_df <- gtfs$stops_df

# create shapes.txt
# needs: shape_id,shape_pt_lat,shape_pt_lon,shape_pt_sequence
prep_shapes <- merge(stops_times_df, stops_df, by="stop_id", all.x=T)
keep <- c("trip_id","stop_lat","stop_lon","stop_sequence")
prep_shapes <- prep_shapes[,keep]
names(prep_shapes) <- c("shape_id","shape_pt_lat","shape_pt_lon","shape_pt_sequence")
trips_df$shape_id <- trips_df$trip_id
write.table(prep_shapes,"shapes.txt",sep=",",row.names=FALSE)
write.table(trips_df,"trips.txt",sep=",",row.names=FALSE)