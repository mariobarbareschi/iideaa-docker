#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <math.h>

#include <map>
#include <vector>

#include "vpa.h"

extern void BlackScholesGPU(float *d_CallResult,
    float *d_PutResult,
    float *d_StockPrice,
    float *d_OptionStrike,
    float *d_OptionYears,
    float Riskfree,
    float Volatility,
    int optN);

const float      RISKFREE = 0.02f;
const float    VOLATILITY = 0.30f;

bool readOracleFile = false;
static float h_StockPrice[40000], h_OptionStrike[40000], h_OptionYears[40000], callResult[40000], putResult[40000], golden_callResult[40000], golden_putResult[40000];
static int oracleLength;

extern "C" double BELLERO_getError() {
    if(!readOracleFile){
        readOracleFile = true;
        /*h_StockPrice = new std::vector<float>(40000);
        h_OptionStrike = new std::vector<float>(40000);
        h_OptionYears = new std::vector<float>(40000);
        callResult = new std::vector<float>(40000);
        putResult = new std::vector<float>(40000);
        golden_callResult = new std::vector<float>(40000);
        golden_putResult = new std::vector<float>(40000);*/
        ::std::ifstream oracle ( "../src/bs_oracle.txt" );
        if ( !oracle.good() ) {
            ::std::cerr << "The oracle does not exist!\n";
            exit ( 1 );
        }
        
        int c = 0; // Counter
        // Read oracle's values
        float h_StockPriceVal, h_OptionStrikeVal, h_OptionYearsVal, golden_callResultVal, golden_putResultVal;
        do {
            oracle >> h_StockPriceVal >> h_OptionStrikeVal >> h_OptionYearsVal >> golden_callResultVal >> golden_putResultVal;
            h_StockPrice[c] = h_StockPriceVal;
            h_OptionStrike[c] = h_OptionStrikeVal;
            h_OptionYears[c] = h_OptionYearsVal;
            golden_callResult[c] = golden_callResultVal;
            golden_putResult[c] = golden_putResultVal;
            c++;
        } while ( !oracle.eof());
        oracleLength = c;
    }
    
    double error = 0;
    int c = 0; // Counter    
    for(c = 0; c < oracleLength; c++){
        BlackScholesGPU(&callResult[c], &putResult[c], &h_StockPrice[c], &h_OptionStrike[c], &h_OptionYears[c], RISKFREE, VOLATILITY, 1000);
        error += sqrt ( pow(golden_callResult[c] - callResult[c], 2) + pow(golden_putResult[c] - putResult[c], 2) );
    }
    return (double)error/c;
}

/*Operators modified by Bellero*/
extern ::vpa::FloatingPointPrecision OP_0, OP_1, OP_2, OP_3, OP_4, OP_5, OP_6, OP_7, OP_8, OP_9, OP_10, OP_11, OP_12, OP_13, OP_14, OP_15, OP_16, OP_17, OP_18, OP_19, OP_20, OP_21, OP_22, OP_23, OP_24, OP_25, OP_26, OP_27, OP_28, OP_29, OP_30, OP_31, OP_32, OP_33;

/*Grouped operators*/

static int getZeros(std::vector<int> v){
    int ret = 0;
    for(int i : v)
        ret += i == 0? 1 : 0;
    return ret;
}

extern "C" double BELLERO_Penality() {

std::map<std::string, ::vpa::FloatingPointPrecision> map_operators;
    
map_operators["OP_0"] = OP_0;
map_operators["OP_1"] = OP_1;
map_operators["OP_2"] = OP_2;
map_operators["OP_3"] = OP_3;
map_operators["OP_4"] = OP_4;
map_operators["OP_5"] = OP_5;
map_operators["OP_6"] = OP_6;
map_operators["OP_7"] = OP_7;
map_operators["OP_8"] = OP_8;
map_operators["OP_9"] = OP_9;
map_operators["OP_10"] = OP_10;
map_operators["OP_11"] = OP_11;
map_operators["OP_12"] = OP_12;
map_operators["OP_13"] = OP_13;
map_operators["OP_14"] = OP_14;
map_operators["OP_15"] = OP_15;
map_operators["OP_16"] = OP_16;
map_operators["OP_17"] = OP_17;
map_operators["OP_18"] = OP_18;
map_operators["OP_19"] = OP_19;
map_operators["OP_20"] = OP_20;
map_operators["OP_21"] = OP_21;
map_operators["OP_22"] = OP_22;
map_operators["OP_23"] = OP_23;
map_operators["OP_24"] = OP_24;
map_operators["OP_25"] = OP_25;
map_operators["OP_26"] = OP_26;
map_operators["OP_27"] = OP_27;
map_operators["OP_28"] = OP_28;
map_operators["OP_29"] = OP_29;
map_operators["OP_30"] = OP_30;
map_operators["OP_31"] = OP_31;
map_operators["OP_32"] = OP_32;
map_operators["OP_33"] = OP_33;
    
        /*for(std::map<std::string, ::vpa::FloatingPointPrecision>::iterator itMap=map_operators.begin(); itMap != map_operators.end(); ++itMap){
            std::cout << itMap->first << " --> (" << itMap->second.mant_size << ", " << itMap->second.exp_size <<")" << std::endl;
        }*/
    
    std::map<std::string, std::vector<int>> usingTypeTable;
    
    std::ifstream vpa_report("../chimera/output/mutants/BlackScholes.cpp/4/vpa_float_report.csv");
    
    ::std::string getLine, OpId;
    ::std::string line;
    ::std::string OpTy, OpRetTy;
    ::std::string Op1, Op2, OpRet; // Operands
    while (!vpa_report.eof()) { //Retrieve a new row from the CSV until exist
        
        vpa_report >> getLine;
        char temp[100];
        std::strcpy(temp,getLine.c_str());
        char* tokenized = std::strtok(temp, ",");
        
        OpId = std::string(tokenized);
        tokenized = std::strtok(NULL, ",");
        line = std::string(tokenized);
        tokenized = std::strtok(NULL, ",");
        OpTy = std::string(tokenized);
        tokenized = std::strtok(NULL, ",");
        OpRetTy = std::string(tokenized);
        tokenized = std::strtok(NULL, ",");
        Op1 = std::string(tokenized);
        Op1.erase(0,1);
        Op1.erase(Op1.end()-1, Op1.end());
        tokenized = std::strtok(NULL, ",");
        Op2 = std::string(tokenized);
        Op2.erase(0,1);
        Op2.erase(Op2.end()-1, Op2.end());
        tokenized = std::strtok(NULL, ",");
        OpRet = std::string(tokenized);
        OpRet.erase(0,1);
        OpRet.erase(OpRet.end()-1, OpRet.end());
        
        //std::cout << OpId << " " << line << " " << OpTy << " " << OpRetTy << " " << Op1 << " " << Op2 << " "<<OpRet << std::endl;
        
        std::map<std::string, ::vpa::FloatingPointPrecision>::iterator it;
        it = map_operators.find(OpId); //try to access the operator OP_XX from the map that has been declared in map_operators
        if(it != map_operators.end()){
            
                std::map<std::string, std::vector<int>>::iterator itOpId;
                itOpId = usingTypeTable.find(OpId);
                if(itOpId == usingTypeTable.end()){
                    usingTypeTable.insert(std::pair<std::string, std::vector<int>>(OpId,{0, 0, 0}));
                    itOpId = usingTypeTable.find(OpId);
                }
                
                if(FPPequals(it->second, vpa::double_prec)){
                            itOpId->second[0]++;
                        } else if(FPPequals(it->second, vpa::float_prec)){
                            itOpId->second[1]++;
                        } else { //half_prec
                            itOpId->second[2]++;
                        }
            
                std::map<std::string, ::vpa::FloatingPointPrecision>::iterator itMapOperatorOp1, itMapOperatorOp2;
                itMapOperatorOp1 = map_operators.find(Op1);
                itMapOperatorOp2 = map_operators.find(Op2);
                
                //let us populate the usingTypeTable with Op1 and Op2
                std::map<std::string, std::vector<int>>::iterator itOp1, itOp2;
                itOp1 = usingTypeTable.find(Op1);
                if(itOp1 == usingTypeTable.end()){
                    usingTypeTable.insert(std::pair<std::string, std::vector<int>>(Op1,{0, 0, 0}));
                    itOp1 = usingTypeTable.find(Op1);
                }
                itOp2 = usingTypeTable.find(Op2);
                if(itOp2 == usingTypeTable.end()){
                    usingTypeTable.insert(std::pair<std::string, std::vector<int>>(Op2,{0, 0, 0}));
                    itOp2 = usingTypeTable.find(Op2);
                }
            
                if(itMapOperatorOp1 != map_operators.end()){ //if the operator is an output of another operation, thus we need to consider the type given by bellerophon
                    //if(false == FPPequals(itMapOperatorOp1->second,it->second) ){
                    //    std::cout << "qui perché diversi"<<std::endl; std::cout.flush();
                        if(FPPequals(it->second, vpa::double_prec)){
                                itOp1->second[0]++;
                        } else if(FPPequals(it->second, vpa::float_prec)){
                                itOp1->second[1]++;
                        } else { //half_prec
                                itOp1->second[2]++;
                        }
                    //}
                } else { //otherwise, it is a constant or an input variable, we must consider its original type (NOT given by bellerophon)
                      /*if(OpRetTy.compare("DOUBLE") == 0){ //Let now us take into accout the original returned type to infer the operands types
                            if(FPPequals(it->second, vpa::float_prec)){
                                itOp1->second[1] = 1;
                            } else if(FPPequals(it->second, vpa::half_prec)){
                                itOp1->second[2] = 1;
                            }
                        } else { //it is float
                            if(FPPequals(it->second, vpa::double_prec)){
                            itOp1->second[0] = 1;
                        } else if(FPPequals(it->second, vpa::half_prec)){
                            itOp1->second[2] = 1;
                        }
                    }*/
                    if(FPPequals(it->second, vpa::double_prec)){
                                itOp1->second[0]++;
                            } else if(FPPequals(it->second, vpa::float_prec)){
                                itOp1->second[1]++;
                            } else {
                                itOp1->second[2]++;
                            }
                    }
            
                if(itMapOperatorOp2 != map_operators.end()){ //if the operator is an output of another operation, thus we need to consider the type given by bellerophon
                    //if(false == FPPequals(itMapOperatorOp2->second, it->second)){
                        if(FPPequals(it->second, vpa::double_prec)){
                                itOp2->second[0]++;
                        } else if(FPPequals(it->second, vpa::float_prec)){
                                itOp2->second[1]++;
                        } else { //half_prec
                                itOp2->second[2]++;
                        }
                    //}
                } else { //otherwise, it is a constant or an input variable, we must consider its original type (NOT given by bellerophon)
                      /*if(OpRetTy.compare("DOUBLE") == 0){ //Let now us take into accout the original returned type to infer the operands types
                            if(FPPequals(it->second, vpa::float_prec)){
                                itOp2->second[1] = 1;
                            } else if(FPPequals(it->second, vpa::half_prec)){
                                itOp2->second[2] = 1;
                            }
                        } else { //it is float
                            if(FPPequals(it->second, vpa::double_prec)){
                            itOp2->second[0] = 1;
                        } else if(FPPequals(it->second, vpa::half_prec)){
                            itOp2->second[2] = 1;
                        }
                    }*/
                    
                    if(FPPequals(it->second, vpa::double_prec)){
                                itOp2->second[0]++;
                            } else if(FPPequals(it->second, vpa::float_prec)){
                                itOp2->second[1]++;
                            } else {
                                itOp2->second[2]++;
                            }
                }
            
        } else {
            std::cerr << "Error: the report do contain unreferenced operators" << std::endl;
            exit(-1);
        }
    }
    
        double penaltyValue = 0.0;
        for(std::map<std::string, std::vector<int>>::iterator itMap=usingTypeTable.begin(); itMap != usingTypeTable.end(); ++itMap){
            //std::cout << itMap->first << " --> " << (int) itMap->second[0] << ", " << (int) itMap->second[1] << ", "<< (int) itMap->second[2] <<std::endl;
            penaltyValue += (2-getZeros(itMap->second));
        }
    return penaltyValue;
}