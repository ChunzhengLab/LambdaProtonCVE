#if !defined(__CINT__) || defined(__MAKECINT__)
#include "TString.h"
#include "TObjArray.h"
#include "TGrid.h"

#include "AliLog.h"

#include "AliAnalysisManager.h"
#include "AliAnalysisDataContainer.h"
#include "AliAnalysisTaskLambdaProtonCVE.h"
#endif

AliAnalysisTaskLambdaProtonCVE* AddTaskLambdaProtonCVE(
    int                              debug=0, // debug level controls amount of output statements
    double                        Harmonic=2,
    TString                    trigger="kMB",
    int                          filterBit=1, // AOD filter bit selection
    int                           nclscut=70, // ncls cut for all tracks 
    float                        chi2max=4.0,
    float                        chi2min=0.1,
    float                        dcacutz=3.2, // dcaz cut for all tracks
    float                       dcacutxy=2.4, // dcaxy cut for all tracks
    float                          ptmin=0.2, // minimum pt for Q-vector components
    float                          ptmax=5.0, // maximum pt for Q-vector components
    bool                      v0calibOn=true,
    bool                           QAV0=true,
    bool                         QATPC=false,
    bool                          doNUE=true,
    bool                          doNUA=true,
    float                        centcut=7.5, // centrality restriction for V0M and TRK
		TString                  period="LHC10h",
    TString	                     uniqueID=""
    )
{	
	// Creates a pid task and adds it to the analysis manager
	// Get the pointer to the existing analysis manager via the static
	//access method
	//=========================================================================
	AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
	if (!mgr) {
		Error("AddTaskCMWESE.C", "No analysis manager to connect to.");
		return NULL;
	}

	// Check the analysis type using the event handlers connected to the
	// analysis manager The availability of MC handler can also be
	// checked here.
	// =========================================================================
	if (!mgr->GetInputEventHandler()) {
		Error("AddTaskCMWESE.C", "This task requires an input event handler");
		return NULL;
	}
	//TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"

  	// --- instantiate analysis task
  	AliAnalysisTaskLambdaProtonCVE *task = new AliAnalysisTaskLambdaProtonCVE("TaskLambdaProtonCVE", period, doNUE, doNUA, v0calibOn);
	task->SetDebug(debug);
	task->SetTrigger(trigger);
	task->SetFilterBit(filterBit);
	task->SetNclsCut(nclscut);
  task->SetChi2Max(chi2max);
  task->SetChi2Min(chi2min);
	task->SetDCAcutZ(dcacutz);
	task->SetDCAcutXY(dcacutxy);
	task->SetPtMin(ptmin);
	task->SetPtMax(ptmax);
	task->SetPeriod(period);
	task->SetV0CalibOn(v0calibOn);
	task->SetV0QAOn(QAV0);
	task->SetNUEOn(doNUE);
	task->SetNUAOn(doNUA);	
	task->SetCentCut(centcut);
	// task->SelectCollisionCandidates(AliVEvent::kINT7);
	mgr->AddTask(task);

	// Create ONLY the output containers for the data produced by the
	// task.  Get and connect other common input/output containers via
	// the manager as below
	//======================================================================
    AliAnalysisDataContainer* cinput  = mgr->GetCommonInputContainer();
		const char* outputFileName = mgr->GetCommonFileName();
  	AliAnalysisDataContainer* coutput = mgr->CreateContainer(Form("output_%s", uniqueID.Data()), TList::Class(), 
                                                           AliAnalysisManager::kOutputContainer,                                                          
                                                           Form("%s:%s", outputFileName, uniqueID.Data()));
   	mgr->ConnectInput (task, 0, cinput);
  	mgr->ConnectOutput(task, 1, coutput);


	Int_t inSlotCounter=1;
	TGrid::Connect("alien://");
        	TObjArray *AllContainers = mgr->GetContainers();

if(doNUE) {
      if (period.EqualTo("LHC10h") || period.EqualTo("LHC11h")) {
                		TFile *inNUE;
			if(!AllContainers->FindObject("NUE")) {
				inNUE = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc10h/Run1NUE.root");
				AliAnalysisDataContainer *cin_NUE = mgr->CreateContainer(Form("NUE"), TList::Class(), AliAnalysisManager::kInputContainer);             
				TList* wNUE_list = NULL;
				wNUE_list = dynamic_cast<TList*>(inNUE->Get("listNUE"));
				if (!wNUE_list) printf("Read TList wrong!\n");
            		    	cin_NUE->SetData(wNUE_list); 			
				mgr->ConnectInput(task,inSlotCounter,cin_NUE);
				inSlotCounter++;
			}
			else {
				mgr->ConnectInput(task,inSlotCounter,(AliAnalysisDataContainer*)AllContainers->FindObject("NUE"));
				inSlotCounter++;
				printf("NUE already loaded\n");
			}
		}	
		else if (period.EqualTo("LHC15o")) {
			TFile *inNUE;
			if(!AllContainers->FindObject("NUE")) {
				inNUE = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc15o/efficiencyBothpol.root");
				// Ref NUE data from alien:///alice/cern.ch/user/p/prottay/nuarootfiles_p5_one_two_two_FB768_15op2_withpileup/efficiencyBothpol.root
				AliAnalysisDataContainer *cin_NUE = mgr->CreateContainer(Form("NUE"), TList::Class(), AliAnalysisManager::kInputContainer);
				TList* wNUE_list = NULL;
				wNUE_list = dynamic_cast<TList*>(inNUE->Get("fMcEffiHij"));
				if (!wNUE_list) printf("Read TList wrong!\n");
            		    	cin_NUE->SetData(wNUE_list); 			
				mgr->ConnectInput(task,inSlotCounter,cin_NUE);
				inSlotCounter++;				
			}
			else {
				mgr->ConnectInput(task,inSlotCounter,(AliAnalysisDataContainer*)AllContainers->FindObject("NUE"));
				inSlotCounter++;
				printf("NUE already loaded\n");
			}
		} 
	}




	if(doNUA) {
		if (period.EqualTo("LHC10h") ) { // NUA for 10h is too large to read, we separate them into 3 TList*s.
			TFile *inNUA;
			if(!AllContainers->FindObject("NUA")) {
				inNUA = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc10h/10hNUAFB1.root");
				AliAnalysisDataContainer *cin_NUA = mgr->CreateContainer(Form("NUA"), TList::Class(), AliAnalysisManager::kInputContainer);				
	                		TList* wNUA_list = NULL;
				wNUA_list = dynamic_cast<TList*>(inNUA->Get("10hListNUAFB1"));
		                	cin_NUA->SetData(wNUA_list); 
				mgr->ConnectInput(task,inSlotCounter,cin_NUA);
				inSlotCounter++;
				
			} else {
				mgr->ConnectInput(task,inSlotCounter,(AliAnalysisDataContainer*)AllContainers->FindObject("NUA"));
				inSlotCounter++;
				printf("NUA already loaded\n");
			}

		} 

		else if (period.EqualTo("LHC15o")) {
			TFile *inNUA;
			if(!AllContainers->FindObject("NUA")) {
				inNUA = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc15o/wgtPion_NUAFB768DeftwPUcut_LHC15op2_24Aug2021.root");
				// Ref NUA data from alien:///alice/cern.ch/user/p/prottay/nuarootfiles_p5_one_two_two_FB768_15op2_withpileup
				// /wgtPion_NUAFB768DeftwPUcut_LHC15op2_24Aug2021.root  (15o_pass2)
				TDirectoryFile* wNUA_directoryfile = (TDirectoryFile*)inNUA->Get("ZDCgains");
				AliAnalysisDataContainer *cin_NUA = mgr->CreateContainer(Form("NUA"), TList::Class(), AliAnalysisManager::kInputContainer);				
				TList* wNUA_list = NULL;
				wNUA_list = dynamic_cast<TList*>(wNUA_directoryfile->Get("fNUA_ChPosChNeg"));
		                	cin_NUA->SetData(wNUA_list); 
				mgr->ConnectInput(task,inSlotCounter,cin_NUA);
				inSlotCounter++;			
			} else {
				mgr->ConnectInput(task,inSlotCounter,(AliAnalysisDataContainer*)AllContainers->FindObject("NUA"));
				inSlotCounter++;
				printf("NUA already loaded\n");
			}
		}

	}




	if(v0calibOn){
		if (period.EqualTo("LHC10h") ) {
			// GainEQ & Recenter
                		TFile *v0calib;
                		if(!AllContainers->FindObject("V0Calib")) {
				AliAnalysisDataContainer *cin_V0Calib = mgr->CreateContainer(Form("V0Calib"), TList::Class(), AliAnalysisManager::kInputContainer);
				v0calib = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc10h/10hQnCalib.root");
                			TList* qncalib_list = NULL;
				qncalib_list = dynamic_cast<TList*>(v0calib->Get("10hlistqncalib"));
                		    	cin_V0Calib->SetData(qncalib_list); 
                		    	mgr->ConnectInput(task,inSlotCounter,cin_V0Calib);
                		    	inSlotCounter++;
                		}else {
				mgr->ConnectInput(task,inSlotCounter,(AliAnalysisDataContainer*)AllContainers->FindObject("V0Calib"));
				inSlotCounter++;
				printf("V0Calib already loaded\n");
			}
		} else if (period.EqualTo("LHC11h")) {
                			printf("lhc11h Calib not been calculated!\n");
      } else if (period.EqualTo("LHC15o")) {}
	}
	


	// Return task pointer at the end
	return task;
}	

