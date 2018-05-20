
DrumTrack kick; 
DrumTrack snare; 
DrumTrack clap; 
DrumTrack hhopen; 
DrumTrack hhclosed; 
DrumTrack hitom; 
DrumTrack lotom; 
DrumTrack *tracks[7]={&kick ,&snare ,&clap ,&hhopen,&hhclosed,&hitom ,&lotom };
byte currentTrack=0;
byte currentCluster=0;

void initTracks(){

	
strcpy(tracks[0]->name, "KICK");
strcpy(tracks[1]->name, "SNARE");
strcpy(tracks[2]->name, "CLAP");
strcpy(tracks[3]->name, "HHOPEN");
strcpy(tracks[4]->name, "HHCLOSED");
strcpy(tracks[5]->name, "HITOM");
strcpy(tracks[6]->name, "LOTOM");
}
