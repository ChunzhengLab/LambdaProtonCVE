// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "AliAnalysisTaskLambdaProtonCVELocal.h"
#include "TInterpreter.h"
#include "AliAnalysisManager.h"
#include "AliAODInputHandler.h"
#include "TMacro.h"
#include "AliAnalysisTaskPIDResponse.h"
#include "AliMultSelectionTask.h"
#include "TSystem.h"
#include "TChain.h"
#include "AliAnalysisAlien.h"
#include "AliPhysicsSelectionTask.h"


void runAnalysis()
{
    // Dataset
    TString dataset = "LHC15o";
    // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
    // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
    Bool_t local      = kFALSE;
    Bool_t gridTest   = kFALSE;
    Bool_t gridRun    = kFALSE;
    Bool_t gridMerge  = kFALSE;
    Bool_t localMerge = kTRUE;

    if (gridMerge || localMerge) gridRun = kFALSE;
    if (gridRun) {
      gridTest = kFALSE;
      local = kFALSE;
    }

    Int_t groupNumber = 2;
    
    // since we will compile a class, tell root where to look for headers  
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif
     
    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    TMacro PIDadd(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C"));
    AliAnalysisTaskPIDResponse* PIDresponseTask = reinterpret_cast<AliAnalysisTaskPIDResponse*>(PIDadd.Exec());
   
    if (dataset.EqualTo("LHC15o") || dataset.EqualTo("LHC18q")) {
      TMacro physicsSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C"));
      AliPhysicsSelectionTask* physicsSelectionTask = reinterpret_cast<AliPhysicsSelectionTask*>(physicsSelection.Exec());
      TMacro multSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"));
      AliMultSelectionTask* multSelectionTask = reinterpret_cast<AliMultSelectionTask*>(multSelection.Exec());
    }
    
    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("AliAnalysisTaskLambdaProtonCVELocal.cxx++g");
    AliAnalysisTaskLambdaProtonCVELocal *task = nullptr;
    if(local)  task = reinterpret_cast<AliAnalysisTaskLambdaProtonCVELocal*>(gInterpreter->ExecuteMacro("AddTaskLambdaProtonCVELocal.C"));
    else       task = reinterpret_cast<AliAnalysisTaskLambdaProtonCVELocal*>(gInterpreter->ExecuteMacro("AddTaskLambdaProtonCVEAlien.C"));
#else
    gROOT->LoadMacro("AliAnalysisTaskLambdaProtonCVELocal.cxx++g");
    gROOT->LoadMacro("AddTaskLambdaProtonCVELocal.C");
    AliAnalysisTaskLambdaProtonCVELocal *task = AddTaskLambdaProtonCVELocal();
#endif


    if(!mgr->InitAnalysis()) return;
    mgr->SetDebugLevel(2);
    mgr->PrintStatus();
    mgr->SetUseProgressBar(1, 25);

    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)
        if(dataset.EqualTo("LHC10h")) chain->Add("/Users/wangchunzheng/alice/data/2010/LHC10h/000139510/ESDs/pass2/AOD160/0247/AliAOD.root");
        if(dataset.EqualTo("LHC15o")) chain->Add("/Users/wangchunzheng/alice/data/2015/LHC15o/000245151/pass2/AOD252/0008/AliAOD.root");
        if(dataset.EqualTo("LHC18q")) chain->Add("/Users/wangchunzheng/alice/data/2018/LHC18q/000295588/pass3/AOD252/AOD/001/AliAOD.root");
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskLambdaProtonCVELocal.cxx AliAnalysisTaskLambdaProtonCVELocal.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskLambdaProtonCVELocal.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20220316_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");

        if (dataset.EqualTo("LHC10h")) {
          //10h
          // select the input data
          alienHandler->SetGridDataDir("/alice/data/2010/LHC10h");
          alienHandler->SetDataPattern("ESDs/pass2/AOD160/*/AliAOD.root");
          // MC has no prefix, data has prefix 000
          alienHandler->SetRunPrefix("000");
          // runnumber
          //1
          if(groupNumber == 1) {
            alienHandler->AddRunNumber(139510);
            alienHandler->AddRunNumber(139507);
            alienHandler->AddRunNumber(139505);
            alienHandler->AddRunNumber(139503);
            alienHandler->AddRunNumber(139465);
            alienHandler->AddRunNumber(139438);
            alienHandler->AddRunNumber(139437);
            alienHandler->AddRunNumber(139360);
            alienHandler->AddRunNumber(139329);
            alienHandler->AddRunNumber(139328);
            alienHandler->AddRunNumber(139314);
            alienHandler->AddRunNumber(139310);
            }
          if(groupNumber == 2) {
            alienHandler->AddRunNumber(139309);
            alienHandler->AddRunNumber(139173);
            alienHandler->AddRunNumber(139107);
            alienHandler->AddRunNumber(139105);
            alienHandler->AddRunNumber(139038);
            alienHandler->AddRunNumber(139037);
            alienHandler->AddRunNumber(139036);
            alienHandler->AddRunNumber(139029);
            alienHandler->AddRunNumber(139028);
            alienHandler->AddRunNumber(138872);
            alienHandler->AddRunNumber(138871);
            alienHandler->AddRunNumber(138870);
          }
          if(groupNumber == 3) {
            alienHandler->AddRunNumber(138837);
            alienHandler->AddRunNumber(138732);
            alienHandler->AddRunNumber(138730);
            alienHandler->AddRunNumber(138666);
            alienHandler->AddRunNumber(138662);
            alienHandler->AddRunNumber(138653);
            alienHandler->AddRunNumber(138652);
            alienHandler->AddRunNumber(138638);
            alienHandler->AddRunNumber(138624);
            alienHandler->AddRunNumber(138621);
            alienHandler->AddRunNumber(138583);
            alienHandler->AddRunNumber(138582);
          }
          if(groupNumber == 4) {
            alienHandler->AddRunNumber(138578);
            alienHandler->AddRunNumber(138534);
            alienHandler->AddRunNumber(138469);
            alienHandler->AddRunNumber(138442);
            alienHandler->AddRunNumber(138439);
            alienHandler->AddRunNumber(138438);
            alienHandler->AddRunNumber(138396);
            alienHandler->AddRunNumber(138364);
            alienHandler->AddRunNumber(138275);
            alienHandler->AddRunNumber(138225);
            alienHandler->AddRunNumber(138201);
            alienHandler->AddRunNumber(138197);
          }
          if(groupNumber == 5) {
            alienHandler->AddRunNumber(138192);
            alienHandler->AddRunNumber(138190);
            alienHandler->AddRunNumber(137848);
            alienHandler->AddRunNumber(137844);
            alienHandler->AddRunNumber(137752);
            alienHandler->AddRunNumber(137751);
            alienHandler->AddRunNumber(137724);
            alienHandler->AddRunNumber(137722);
            alienHandler->AddRunNumber(137718);
            alienHandler->AddRunNumber(137704);
            alienHandler->AddRunNumber(137693);
            alienHandler->AddRunNumber(137692);
          }
          if(groupNumber == 6) {
            alienHandler->AddRunNumber(137691);
            alienHandler->AddRunNumber(137686);
            alienHandler->AddRunNumber(137685);
            alienHandler->AddRunNumber(137639);
            alienHandler->AddRunNumber(137638);
            alienHandler->AddRunNumber(137608);
            alienHandler->AddRunNumber(137595);
            alienHandler->AddRunNumber(137549);
            alienHandler->AddRunNumber(137546);
            alienHandler->AddRunNumber(137544);
            alienHandler->AddRunNumber(137541);
            alienHandler->AddRunNumber(137539);
          }
          if(groupNumber == 7) {
            alienHandler->AddRunNumber(137531);
            alienHandler->AddRunNumber(137530);
            alienHandler->AddRunNumber(137443);
            alienHandler->AddRunNumber(137441);
            alienHandler->AddRunNumber(137440);
            alienHandler->AddRunNumber(137439);
            alienHandler->AddRunNumber(137434);
            alienHandler->AddRunNumber(137432);
            alienHandler->AddRunNumber(137431);
            alienHandler->AddRunNumber(137430);
            alienHandler->AddRunNumber(137243);
            alienHandler->AddRunNumber(137236);
            alienHandler->AddRunNumber(137235);
          }
          if(groupNumber == 8) {
            alienHandler->AddRunNumber(137232);
            alienHandler->AddRunNumber(137231);
            alienHandler->AddRunNumber(137230);
            alienHandler->AddRunNumber(137162);
            alienHandler->AddRunNumber(137161);
            alienHandler->AddRunNumber(138732);
          }
        }
        if (dataset.EqualTo("LHC15o")) {
          // select the input data
          alienHandler->SetGridDataDir("/alice/data/2015/LHC15o");
          alienHandler->SetDataPattern("pass2/AOD252/AOD/*/AliAOD.root");
          // MC has no prefix, data has prefix 000
          alienHandler->SetRunPrefix("000");
          groupNumber = 0;
          alienHandler->AddRunNumber(245952);
          alienHandler->AddRunNumber(245949);
          alienHandler->AddRunNumber(245923);
          alienHandler->AddRunNumber(245833);
          alienHandler->AddRunNumber(245831);
          alienHandler->AddRunNumber(245829);
          alienHandler->AddRunNumber(245793);
        }
        if (dataset.EqualTo("LHC18q")) {
          // select the input data
          alienHandler->SetGridDataDir("/alice/data/2018/LHC18q");
          alienHandler->SetDataPattern("pass3/AOD252/AOD/*/AliAOD.root");
          // MC has no prefix, data has prefix 000
          alienHandler->SetRunPrefix("000");
          groupNumber = 0;
          alienHandler->AddRunNumber(296135);
          alienHandler->AddRunNumber(296134);
          alienHandler->AddRunNumber(296133);
          alienHandler->AddRunNumber(296132);
          alienHandler->AddRunNumber(296123);
          alienHandler->AddRunNumber(296074);
          alienHandler->AddRunNumber(296066);
        }
    
        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(40);
        alienHandler->SetExecutable("myTask.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("myTask.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with kTRUE to merge on grid
        // after re-running the jobs in SetRunMode("terminate") 
        // (see below) mode, set SetMergeViaJDL(kFALSE) 
        // to collect final results
        alienHandler->SetMaxMergeStages(1);
        if(gridRun || gridMerge) {
          alienHandler->SetMergeViaJDL(kTRUE);
        }
        if (localMerge) {
          alienHandler->SetMergeViaJDL(kFALSE);
        }

        // define the output folders
        if (dataset.EqualTo("LHC10h")) alienHandler->SetGridWorkingDir("LambdaProtonCVELocal/LHC10h");
        if (dataset.EqualTo("LHC15o")) alienHandler->SetGridWorkingDir("LambdaProtonCVELocal/LHC15o");
        if (dataset.EqualTo("LHC18q")) alienHandler->SetGridWorkingDir("LambdaProtonCVELocal/LHC18q");
        if(groupNumber == 0) alienHandler->SetGridOutputDir("output_0");
        if(groupNumber == 1) alienHandler->SetGridOutputDir("output_1");
        if(groupNumber == 2) alienHandler->SetGridOutputDir("output_2");
        if(groupNumber == 3) alienHandler->SetGridOutputDir("output_3");
        if(groupNumber == 4) alienHandler->SetGridOutputDir("output_4");
        if(groupNumber == 5) alienHandler->SetGridOutputDir("output_5");
        if(groupNumber == 6) alienHandler->SetGridOutputDir("output_6");
        if(groupNumber == 7) alienHandler->SetGridOutputDir("output_7");
        if(groupNumber == 8) alienHandler->SetGridOutputDir("output_8");

        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis
            if(gridMerge || localMerge) alienHandler->SetRunMode("terminate");
            if(gridRun)   alienHandler->SetRunMode("full");
            mgr->StartAnalysis("grid");
        }
    }
}

