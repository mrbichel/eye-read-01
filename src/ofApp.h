
//
//  ofxParagraphExample
//
//  Created by Stephen Braitsch on 9/17/15
//  https://github.com/braitsch/ofxParagraph
//

#pragma once
#include "ofMain.h"
#include "Paragraph.hpp"

#define MSGPACK_DISABLE_LEGACY_NIL
#include <msgpack.hpp>
#include <zmq.hpp>

//#include <azmq/socket.hpp>
//#include <boost/asio.hpp>
//#include <array>


const string text1 = "Vi var kommet forbi striben af firkantede lodder, flade, bortset fra de gule etplanshuse, der var skudt op på nogle af dem. Og så lå den der pludselig, vejen. Den var ryddet for sne og skar sig gennem alt det hvide i begge retninger, så langt man kunne se. Det så pænt ud. Måske forstærket af alt roderiet bag os, stierne, grusvejene, markerne og byggepladserne, som vi ikke kunne hitte ud af. På den anden side var en mark, hvid og med striber af sort, fuget jord. Den fortsatte udefter og over i en gråhvid dis. Det var et mærkeligt sted, så langt væk, man kunne komme, og med universet og rummet trukket tæt på. Vi spurgte, om vi var der, om det var dét her. Så løftede han armen og pegede ud over marken, som om han ville kommandere os fremad eller sige “dér ovre, lige på den anden side.” Det samme sted eller lidt derfra stod en række kæmpestore betonskeletter, uhyggelige, levende væsener og samtidig papirstynde og skrøbelige og så bittesmå, at man kunne løfte dem op i hånden eller vælte dem ét ad gangen med et puf med det yderste af fingrene. De så fine ud, række efter række og en lille smule forskudt i en skrå linje bagud. Nedefra var de oplyst af projektører, der skar dem fri af mørket og trak dem tættere på, så de i nogle feberagtige, svimlende sekunder så ud til at ville lette. Og så gik vi hjem. Imens fortalte han en af sine historier. Til sidst bar han mig. Det er det år, mine forældre er blevet skilt. Det samme er Louis’ forældre eller gået fra hinanden, for de var ikke rigtig gift ligesom mine. Det var hans mor, der gik, eller løb, hele vejen til Sønderjylland efter at være blevet gennembanket i årevis. Kort før den dag på grillbaren var skoleinspektøren kommet midt i en musiktime og havde givet mig et brev fra Louis, hvor han fortalte det hele. Han skrev også, at hans mor var dum.";


struct Gaze
{
    //public:
        std::string topic;
        float norm_pos [2];
        float eye_center_3d [3];
        float gaze_normal_3d [3];
        float gaze_point_3d [3];
        
        float confidence;
        float timestamp; // cast to time / unsigned long int - seems to be float in the msgpack encoding
    
        msgpack::object base_data; // 'base_data': [<pupil datum>]
        MSGPACK_DEFINE_MAP(topic, norm_pos, eye_center_3d, gaze_normal_3d, gaze_point_3d, confidence, timestamp, base_data);
};


class PupilZmq
{
    
    public:
    /*void threadedFunction()
    {
        while(isThreadRunning())
        {
            
        }
    }*/
    

    
    void connect(string addr);
    
    void receive();
    
    Gaze gaze;
    
    std::string getApiAddress(string addr, int port) {
        std::stringstream ss;
        ss << "tcp://" << addr << ":" << port;
        return ss.str();
    }
    
    protected:
    zmq::socket_t socket;
    zmq::pollitem_t items[1];
    
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        void update();
    
        vector<Paragraph*> paragraphs;
    
    ofShader shader;
    ofPlanePrimitive plane;
        
    ofFbo fbo1;
    ofTexture tex1;
    
    PupilZmq pupilZmq;
    
    float x;
    float y;
    
    //zmq::socket_t req_socket;
    // zmq::socket_t * sub_socket;
    //
    
    
    
};






/* example msgpack data
{"topic":"gaze.3d.1.",
    "norm_pos":[0.171095,0.661531],
    "eye_center_3d":[14.7901,76.424,124.037],
    "gaze_normal_3d":[-0.585709,-0.252092,0.770321],
    "gaze_point_3d":[-549.248,-166.341,865.855],
    "confidence":0.288941,
    "timestamp":314099,
    "base_data":[
        {"circle_3d":{"center":[0.248564,0.340241,3.23776],"normal":[-0.57931,0.163686,-0.798503],"radius":0.0282597},
            "confidence":0.288941,
            "timestamp":314099,
            "diameter_3d":0.0565194,
            "ellipse":{"center":[143.621,161.149],
            "axes":[8.86519,10.9114],
            "angle":-26.0557},
            "location":[143.621,161.149],
            "diameter":10.9114,
            "sphere":{
                    "center":[7.20028,-1.62399,12.8198],
                    "radius":12},
                 "projected_sphere":{
                    "center":[444.225,17.4592],
                    "axes":[1160.71,1160.71],
                    "angle":90},
                 "model_confidence":1,
                 "model_id":141,
                 "model_birth_timestamp":313692,
                 "theta":1.73522,
                 "phi":-2.19843,
                 "norm_pos":[0.748025,0.160685],
                 "topic":"pupil.1",
                 "id":1,
                 "method":"3d c++"}
 ]
 }
*/