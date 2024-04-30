#include NFDHAlgorithm.h

NFDHAlgorithm(){

}

void runAlgorithm(std::vector<Rect> RectList, std::vector<Bin> BinList){
    
    //Version naïve où l'on créé autant de bin qu'il y a de rectangle => 1 rectangle / bin 
    /*for (int i=0 ; i<RectList.size() ; i++){
        Bin bin=new Bin();
        bin.addRectangle(RectList.get(i)) ; 
        rectList.get(i).setBinId(i); 
        BinList.add(bin) ; 
    }*/

    /*
    vraie version de l'algorithme NFDH : 
    Pour chaque rectangle r de notre liste, on essaie de mettre celui-ci dans la bin actuelle
    Si cela passe, pas de changement, on ajoute simplement r à la bin actuelle en modifiant l'id_bin de r 
    Dans le cas inverse, on créé une nouvelle bin pour accueillir r. A nouveau, on modifie l'id_bin de r 
    */

    Bin bin=new Bin();
    BinList.add(bin);
    int nbrBin=0 ; 
    for (int i=0 ; i<RectList.size() ; i++){
        Bin currentBin=BinList.get(nbrBin) ; 
        Rect currentRect=RectList.get(i) ; 
        double aire=currentRect.getHeight()*currentRect.getWidth() ; 
        if (current.getEmptySpace>aire){
            //TODO : vérifier plus précisément les collisions 
            currentBin.addRectangle(currentRect) ; 
        }else{
            Bin newBin=new Bin();
            nbrBin++ ; 
            newBin.addRectangle(currentRect) ; 
            BinList.add(newBin) ; 
        }
        currentRect.setBinId=nbrBin ; 
    }


}