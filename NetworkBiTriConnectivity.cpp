#include <ogdf/basic/graph_generators.h>
#include <ogdf/planarity/SubgraphPlanarizer.h>
#include <ogdf/planarity/PlanarSubgraphFast.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/basic/GraphList.h>
#include <ogdf/basic/Graph_d.h> 
#include <ogdf/basic/GraphCopy.h>
#include <ogdf/basic/Graph.h>
#include <ogdf/decomposition/DynamicSPQRForest.h>
#include <ogdf/decomposition/SPQRTree.h>
#include <ogdf/decomposition/DynamicSPQRTree.h>
#include <ogdf/decomposition/SPQRTree.h>
#include <ogdf/decomposition/DynamicSPQRForest.h>
#include <ogdf/decomposition/DynamicSkeleton.h>
#include <ogdf/decomposition/BCTree.h>
#include <iostream>
#include <fstream>
#include <ogdf/fileformats/GraphIO.h>
#include <algorithm>


using namespace ogdf;
using namespace std; 
int main()
{

	Graph  G ;
    int length=20 ;
    
    int num_real_nodes=length*length ;
    int num_total_nodes= 4*length*length ;
    int num_real_edges= 2*length*length ;
    Array<node> nodes(num_total_nodes);
    Array<node> source_nodes(num_real_edges);
    Array<node> target_nodes(num_real_edges);
    int ind[num_real_edges];

    for( int i = 0; i < num_total_nodes ; i = i + 1 ) {

	     nodes[i]=G.newNode() ;
	     
	     if  ((i%4)==1) {

	     	G.newEdge(nodes[i],nodes[i-1]) ;
	     }
	     if  ((i%4)==2) {
	     	G.newEdge(nodes[i],nodes[i-1]) ;

	     }
	     if  ((i%4)==3) {
	     	G.newEdge(nodes[i],nodes[i-1]) ;
	     	G.newEdge(nodes[i],nodes[i-3]) ;

	     }

	     //cout<<G.numberOfNodes()<<endl ;
	     cout<<G.numberOfEdges()<<endl ;
     }
     int internal_node_index ;
     int node_index ;
     int k ;
     k=0 ;
     for( int i = 0; i < num_total_nodes ; i = i + 1 ) {

         ind[k]= k ;

       node_index= ((int)i / 4) + 1;
       internal_node_index= (i%4) + 1 ;
       if (internal_node_index==1){
       	  
       	  source_nodes[k]=nodes[i] ;
       	  
       	  
           if (((node_index+1)% (num_real_nodes))==0) {

              target_nodes[k]= nodes[num_total_nodes-2] ;

           }
           if (((node_index)% (length))==0) {

              target_nodes[k]= nodes[(i-(node_index-1)*4)+1] ;

           }
           else {
           	   target_nodes[k]=nodes[i+5] ;


           }


           //G.newEdge(source_nodes[k],target_nodes[k]) ;

           k=k+1 ;
       }

       if (internal_node_index==3){
       	  
       	  source_nodes[k]=nodes[i] ;
       	  
       	  
       	   if (((node_index+length)% (num_real_nodes))==0) {

              target_nodes[k]= nodes[num_total_nodes-1] ;

           }
           else {
           	  if (node_index>(length*(length-1))){

           	  	target_nodes[k]=nodes[((int) node_index/ length)*4 -1] ;

           	  }
           	  else {
              target_nodes[k]=nodes[(node_index+length)*4 -1] ;
              }

           }



           //G.newEdge(source_nodes[k],target_nodes[k]) ;

           k=k+1 ;


       }

       cout<<"edges "<<G.numberOfEdges()<<endl ;
       cout<<node_index<<endl ;
       cout<<internal_node_index<<endl ;

       cout<<"k="<<k<<endl ;

       cout<<"ind="<<ind[k]<<endl ;




     }

    int shuffled[num_real_edges];
    random_shuffle(&ind[0], &ind[num_real_edges]);

    
    cout<<sizeof(ind)/sizeof(*ind)<<endl ;

     /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

DynamicBCTree*  K=new DynamicBCTree(G,true) ;
cout<<"numbcomps="<<K->numberOfBComps()<<endl ;
cout<<"numccomps="<<K->numberOfCComps()<<endl ;

for (int i=0; i<num_real_edges; i=i+ 1) {

    //edge NEW=G.newEdge(source_nodes[i],target_nodes[i]) ; 

    //K->updateInsertedEdge(NEW) ; 
    
	K->insertEdge(source_nodes[i],target_nodes[i]) ;

	Graph HH=K->bcTree() ;
        int max=0 ;
        for(node h : HH.nodes) {
            int A=K->numberOfNodes(h) ;
              
            if (A>max) {
                max=A; 
                        
            }    
        }
        cout<<i<<"I am in else max="<<max<<endl;
    cout<<"edges "<<G.numberOfEdges()<<endl ;
    	
    }






	
    
  return 0;
}



