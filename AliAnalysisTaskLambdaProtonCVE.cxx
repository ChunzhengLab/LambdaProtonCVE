/*************************************************************************
 * Copyright(c) 1998-2008, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

//--------------------------------------------------------------------------------
// CVE analysis
// Contributor: Chunzheng Wang, <chunzheng.wang@cern.ch>, shanghai
//--------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <sys/time.h>
// ROOT classes
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
#include "TExMap.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TComplex.h"
#include "TSpline.h"
#include "TGrid.h"
// Alice analysis base class
#include "AliAnalysisTaskSE.h"
// Alice analysis additional classes
#include "AliAnalysisManager.h"
#include "AliInputEventHandler.h"
// Alice AOD classes
#include "AliAODInputHandler.h"
#include "AliAODHandler.h"
#include "AliAODEvent.h"
#include "AliAODVertex.h"
#include "AliAODVZERO.h"
// Alice classes
#include "AliCentrality.h"
#include "AliEventplane.h"
#include "AliEventCuts.h"
#include "AliAnalysisUtils.h"
// Alice MC classes
#include "AliMCEvent.h"
#include "AliMCEventHandler.h"
#include "AliAODMCParticle.h"
// Alice "V" classes
#include "AliVParticle.h"
#include "AliVEvent.h"
#include "AliVVertex.h"
#include "AliVVZERO.h"
// Alice PID classes
#include "AliAODPid.h"
#include "AliAODpidUtil.h"
#include "AliPID.h"
#include "AliPIDCombined.h"
#include "AliPIDResponse.h"
#include "AliMultSelection.h"
#include "AliOADBContainer.h"
#include "AliCentrality.h"
#include "AliAnalysisTaskLambdaProtonCVE.h"

using std::cout;
using std::endl;

ClassImp(AliAnalysisTaskLambdaProtonCVE);

//---------------------------------------------------

AliAnalysisTaskLambdaProtonCVE::AliAnalysisTaskLambdaProtonCVE() : 
  AliAnalysisTaskSE(), 
  fDebug(0),
  fTrigger("kMB"),
  fPeriod("LHC10h"),

  fCentDiffCut(7.5),
  fQAV0(true),
  fV0CalibOn(true),
  fTPCCalibOn(false),

  fPlanePtMin(0.2),
  fPlanePtMax(2.0),
  fEtaGapPos( 0.1),
  fEtaGapNeg(-0.1),

  fFltbit(1),
  fNclsCut(70),
  fChi2Max(4.0),
  fChi2Min(0.1),
  fDcaCutz(3.2),
  fDcaCutxy(2.4),
  fPtMin(0.2),
  fPtMax(5.0),
  fDoNUE(true),
  fDoNUA(true),

  fNSigmaTPCCut(4),
  fNSigmaTOFCut(4),

  fV0PtMin(0.5),
  fV0CPAMin(0.995),
  fV0RapidityMax(0.5),
  fV0DecayLengthMin(3.),
  fV0DecayLengthMax(100.),
  fV0DCAToPrimVtxMax(1.5),
  fV0DcaBetweenDaughtersMax(1.),

  fDaughtersPtMax(20.),
  fDaughtersNsigma(3.),
  fDaughtersEtaMax(0.8),
  fDaughtersTPCNclsMin(70),
  fDaughtersDCAToPrimVtxMin(0.02),
  fV0PosProtonTPCNsigma(4.),
  fV0NegPionTPCNsigma(4.),
  fV0NegProtonTPCNsigma(4.),
  fV0PosPionTPCNsigma(4.),
  fV0DaughterUseTOF(false),
  fV0PosProtonTOFNsigma(4.),
  fV0NegPionTOFNsigma(4.),
  fV0NegProtonTOFNsigma(4.),
  fV0PosPionTOFNsigma(4.),

  fMassMean(1.115683),
  fLambdaMassCut(0.005),

  fIsCheckPIDFlow(false),

  fEtaCut(0.8),
  fDedxCut(10.0),
  fZvtxCut(10.0),
  fPUSyst(-1),


  fAOD(nullptr),         //! aod Event
  fPIDResponse(nullptr), //! PID Handler
  fUtils(nullptr),       //! Event Selection Options
  fVtx(nullptr),

  fRunNum(-999), // runnumber
  fRunNumBin(-999), // runnumer bin, 10:139510..., 11:170387..., 15HIR:246994...
  fVzBin(-999), // vertex z bin
  fCentBin(-999), // centrality bin: 0-10
  fCent(-999), // value of centrality 
  fPsi2V0M(-999),
  fPsi2V0C(-999),
  fPsi2V0A(-999),
  fPsi2TPCPos(-999),
  fPsi2TPCNeg(-999),


  fListNUE(nullptr),
  fListNUA(nullptr),
  fListVZEROCALIB(nullptr),

  hNUEweightPlus(nullptr),
  hNUEweightMinus(nullptr), 
  hNUAweightPlus(nullptr),
  hNUAweightMinus(nullptr),
  hCorrectNUAPos(nullptr),
  hCorrectNUANeg(nullptr),
  hMultV0Read(nullptr),
  fSPDCutPU(nullptr),
  fV0CutPU(nullptr),
  fCenCutLowPU(nullptr),
  fCenCutHighPU(nullptr),
  fMultCutPU(nullptr),

  fOutputList(nullptr),
  hEvtCount(nullptr),
  hRunNumBin(nullptr),
  hPt(nullptr),
  hPDedx(nullptr),


  hV0CV0APsi2Correlation(nullptr),
  hV0CTPCPosPsi2Correlation(nullptr),
  hV0ATPCPosPsi2Correlation(nullptr),
  hV0CTPCNegPsi2Correlation(nullptr),
  hV0ATPCNegPsi2Correlation(nullptr),

  fHistV0Pt(nullptr),              
  fHistV0Eta(nullptr),              
  fHistV0DcatoPrimVertex(nullptr), 
  fHistV0CPA(nullptr),             
  fHistV0DecayLength(nullptr),     
  fProfileDelta_Lambda_hPos(nullptr),
  fProfileDelta_Lambda_hNeg(nullptr),
  fProfileDelta_Lambda_Proton(nullptr),   
  fProfileDelta_Lambda_AntiProton(nullptr),
  fProfileDelta_AntiLambda_hPos(nullptr),
  fProfileDelta_AntiLambda_hNeg(nullptr),
  fProfileDelta_AntiLambda_Proton(nullptr),
  fProfileDelta_AntiLambda_AntiProton(nullptr),    
  fProfileGammaTPC_Lambda_hPos(nullptr),
  fProfileGammaTPC_Lambda_hNeg(nullptr),
  fProfileGammaTPC_Lambda_Proton(nullptr),
  fProfileGammaTPC_Lambda_AntiProton(nullptr),
  fProfileGammaTPC_AntiLambda_hPos(nullptr),
  fProfileGammaTPC_AntiLambda_hNeg(nullptr),
  fProfileGammaTPC_AntiLambda_Proton(nullptr),
  fProfileGammaTPC_AntiLambda_AntiProton(nullptr),  
  fProfileGammaV0C_Lambda_hPos(nullptr),
  fProfileGammaV0C_Lambda_hNeg(nullptr),
  fProfileGammaV0C_Lambda_Proton(nullptr),
  fProfileGammaV0C_Lambda_AntiProton(nullptr),
  fProfileGammaV0C_AntiLambda_hPos(nullptr),
  fProfileGammaV0C_AntiLambda_hNeg(nullptr),
  fProfileGammaV0C_AntiLambda_Proton(nullptr),
  fProfileGammaV0C_AntiLambda_AntiProton(nullptr),
  fProfileGammaV0A_Lambda_hPos(nullptr),
  fProfileGammaV0A_Lambda_hNeg(nullptr),
  fProfileGammaV0A_Lambda_Proton(nullptr),
  fProfileGammaV0A_Lambda_AntiProton(nullptr),
  fProfileGammaV0A_AntiLambda_hPos(nullptr),
  fProfileGammaV0A_AntiLambda_hNeg(nullptr),
  fProfileGammaV0A_AntiLambda_Proton(nullptr),
  fProfileGammaV0A_AntiLambda_AntiProton(nullptr)
{
  for (int i = 0; i < 3; i++)    fVetex[i] = -999;
  for (int i = 0; i < 3; ++i)    pV0XMeanRead[i] = nullptr; 
  for (int i = 0; i < 3; ++i)    pV0YMeanRead[i] = nullptr;

  hMultV0=nullptr; //Dobrin
  for (int i = 0; i < 2; ++i)  hQx2mV0[i] = nullptr;
  for (int i = 0; i < 2; ++i)  hQy2mV0[i] = nullptr;
  for (int i = 0; i < 64; ++i) fMultV0Ch[i] = -999.;
  for (int i = 0; i < 3; ++i)  fV0XMean[i]  = -999.;
  for (int i = 0; i < 3; ++i)  fV0YMean[i]  = -999.;

  for (int i = 0; i < 2; ++i) hCent[i]   = nullptr;
  for (int i = 0; i < 2; ++i) hVz[i]     = nullptr;

  for (int i = 0; i < 8; ++i) hCentQA[i]     = nullptr;
  for (int i = 0; i < 2; ++i) hMultCentQA[i] = nullptr;
  for (int i = 0; i < 6; ++i) hMultMultQA[i] = nullptr;

  for (int i = 0; i < 2; ++i) hEta[i]    = nullptr;
  for (int i = 0; i < 2; ++i) hPhi[i]    = nullptr;
  for (int i = 0; i < 2; ++i) hEtaPhi[i] = nullptr;
  for (int i = 0; i < 2; ++i) hDcaXy[i]  = nullptr;
  for (int i = 0; i < 2; ++i) hDcaZ[i]   = nullptr;
  for (int i = 0; i < 2; ++i) hNhits[i]  = nullptr;

  for (int i = 0; i < 3; ++i) hQxCentRecenter[i] = nullptr;
  for (int i = 0; i < 3; ++i) hQxVtxRecenter[i]  = nullptr;
  for (int i = 0; i < 3; ++i) hQyCentRecenter[i] = nullptr;
  for (int i = 0; i < 3; ++i) hQyVtxRecenter[i]  = nullptr;
  for (int i = 0; i < 3; ++i) hQnCentRecenter[i] = nullptr;
  for (int i = 0; i < 10; ++i) for (int j = 0; j < 3; ++j) hPsiV0Recenter[i][j] = nullptr;

  for (int i = 0; i < 2; i++) {
    fHistLambdaPt[i]                  = nullptr;            
    fHistLambdaEta[i]                 = nullptr;
    fHistLambdaPhi[i]                 = nullptr;
    fHistLambdaDcaToPrimVertex[i]     = nullptr;
    fHistLambdaCPA[i]                 = nullptr;
    fHistLambdaDecayLength[i]         = nullptr;
    fHistLambdaMass[i]                = nullptr;
    fHistAntiLambdaPt[i]              = nullptr;
    fHistAntiLambdaEta[i]             = nullptr;
    fHistAntiLambdaPhi[i]             = nullptr;
    fHistAntiLambdaDcaToPrimVertex[i] = nullptr;
    fHistAntiLambdaCPA[i]             = nullptr;
    fHistAntiLambdaDecayLength[i]     = nullptr;
    fHistAntiLambdaMass[i]            = nullptr;
    fProfileLambdaMassVsPt[i]         = nullptr;
    fProfileAntiLambdaMassVsPt[i]     = nullptr;
  }  

  for (int i = 0; i < 3; i++) {
    fHist3DdNdPhiCentPthPos[i] = nullptr;
    fHist3DdNdPhiCentPthNeg[i] = nullptr;  
    fHist3DdNdPhiCentPtProton[i] = nullptr;
    fHist3DdNdPhiCentPtAntiProton[i] = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    fHist3DdNdPhiCentPtLambda[i] = nullptr;
    fHist3DdNdPhiCentPtAntiLambda[i] = nullptr;
  }  
}

//---------------------------------------------------

AliAnalysisTaskLambdaProtonCVE::AliAnalysisTaskLambdaProtonCVE(const char *name, TString _PR, bool _NUE, bool _NUA, bool _V0Calib) : 
  AliAnalysisTaskSE(name), 
  fDebug(0),
  fTrigger("kMB"),
  fPeriod("LHC10h"),

  fCentDiffCut(7.5),
  fQAV0(true),
  fV0CalibOn(true),
  fTPCCalibOn(false),

  fPlanePtMin(0.2),
  fPlanePtMax(2.0),
  fEtaGapPos( 0.1),
  fEtaGapNeg(-0.1),

  fFltbit(1),
  fNclsCut(70),
  fChi2Max(4.0),
  fChi2Min(0.1),
  fDcaCutz(3.2),
  fDcaCutxy(2.4),
  fPtMin(0.2),
  fPtMax(5.0),
  fDoNUE(true),
  fDoNUA(true),

  fNSigmaTPCCut(4),
  fNSigmaTOFCut(4),

  fV0PtMin(0.5),
  fV0CPAMin(0.995),
  fV0RapidityMax(0.5),
  fV0DecayLengthMin(3.),
  fV0DecayLengthMax(100.),
  fV0DCAToPrimVtxMax(1.5),
  fV0DcaBetweenDaughtersMax(1.),

  fDaughtersPtMax(20.),
  fDaughtersNsigma(3.),
  fDaughtersEtaMax(0.8),
  fDaughtersTPCNclsMin(70),
  fDaughtersDCAToPrimVtxMin(0.02),
  fV0PosProtonTPCNsigma(4.),
  fV0NegPionTPCNsigma(4.),
  fV0NegProtonTPCNsigma(4.),
  fV0PosPionTPCNsigma(4.),
  fV0DaughterUseTOF(false),
  fV0PosProtonTOFNsigma(4.),
  fV0NegPionTOFNsigma(4.),
  fV0NegProtonTOFNsigma(4.),
  fV0PosPionTOFNsigma(4.),

  fMassMean(1.115683),
  fLambdaMassCut(0.005),

  fIsCheckPIDFlow(false),
  fEtaCut(0.8),
  fDedxCut(10.0),
  fZvtxCut(10.0),
  fPUSyst(-1),

  fAOD(nullptr),         //! aod Event
  fPIDResponse(nullptr), //! PID Handler
  fUtils(nullptr),       //! Event Selection Options
  fVtx(nullptr),

  fRunNum(-999), // runnumber
  fRunNumBin(-999), // runnumer bin, 10:139510..., 11:170387..., 15HIR:246994...
  fVzBin(-999), // vertex z bin
  fCentBin(-999), // centrality bin: 0-10
  fCent(-999), // value of centrality 
  fPsi2V0M(-999),
  fPsi2V0C(-999),
  fPsi2V0A(-999),
  fPsi2TPCPos(-999),
  fPsi2TPCNeg(-999),


  fListNUE(nullptr),
  fListNUA(nullptr),
  fListVZEROCALIB(nullptr),

  hNUEweightPlus(nullptr),
  hNUEweightMinus(nullptr), 
  hNUAweightPlus(nullptr),
  hNUAweightMinus(nullptr),
  hCorrectNUAPos(nullptr),
  hCorrectNUANeg(nullptr),
  hMultV0Read(nullptr),
  fSPDCutPU(nullptr),
  fV0CutPU(nullptr),
  fCenCutLowPU(nullptr),
  fCenCutHighPU(nullptr),
  fMultCutPU(nullptr),

  fOutputList(nullptr),
  hEvtCount(nullptr),
  hRunNumBin(nullptr),
  hPt(nullptr),
  hPDedx(nullptr),


  hV0CV0APsi2Correlation(nullptr),
  hV0CTPCPosPsi2Correlation(nullptr),
  hV0ATPCPosPsi2Correlation(nullptr),
  hV0CTPCNegPsi2Correlation(nullptr),
  hV0ATPCNegPsi2Correlation(nullptr),

  fHistV0Pt(nullptr),              
  fHistV0Eta(nullptr),              
  fHistV0DcatoPrimVertex(nullptr), 
  fHistV0CPA(nullptr),             
  fHistV0DecayLength(nullptr),     
  fProfileDelta_Lambda_hPos(nullptr),
  fProfileDelta_Lambda_hNeg(nullptr),
  fProfileDelta_Lambda_Proton(nullptr),   
  fProfileDelta_Lambda_AntiProton(nullptr),
  fProfileDelta_AntiLambda_hPos(nullptr),
  fProfileDelta_AntiLambda_hNeg(nullptr),
  fProfileDelta_AntiLambda_Proton(nullptr),
  fProfileDelta_AntiLambda_AntiProton(nullptr),    
  fProfileGammaTPC_Lambda_hPos(nullptr),
  fProfileGammaTPC_Lambda_hNeg(nullptr),
  fProfileGammaTPC_Lambda_Proton(nullptr),
  fProfileGammaTPC_Lambda_AntiProton(nullptr),
  fProfileGammaTPC_AntiLambda_hPos(nullptr),
  fProfileGammaTPC_AntiLambda_hNeg(nullptr),
  fProfileGammaTPC_AntiLambda_Proton(nullptr),
  fProfileGammaTPC_AntiLambda_AntiProton(nullptr),  
  fProfileGammaV0C_Lambda_hPos(nullptr),
  fProfileGammaV0C_Lambda_hNeg(nullptr),
  fProfileGammaV0C_Lambda_Proton(nullptr),
  fProfileGammaV0C_Lambda_AntiProton(nullptr),
  fProfileGammaV0C_AntiLambda_hPos(nullptr),
  fProfileGammaV0C_AntiLambda_hNeg(nullptr),
  fProfileGammaV0C_AntiLambda_Proton(nullptr),
  fProfileGammaV0C_AntiLambda_AntiProton(nullptr),
  fProfileGammaV0A_Lambda_hPos(nullptr),
  fProfileGammaV0A_Lambda_hNeg(nullptr),
  fProfileGammaV0A_Lambda_Proton(nullptr),
  fProfileGammaV0A_Lambda_AntiProton(nullptr),
  fProfileGammaV0A_AntiLambda_hPos(nullptr),
  fProfileGammaV0A_AntiLambda_hNeg(nullptr),
  fProfileGammaV0A_AntiLambda_Proton(nullptr),
  fProfileGammaV0A_AntiLambda_AntiProton(nullptr)
{
  for (int i = 0; i < 3; i++)    fVetex[i] = -999;
  for (int i = 0; i < 3; ++i)    pV0XMeanRead[i] = nullptr; 
  for (int i = 0; i < 3; ++i)    pV0YMeanRead[i] = nullptr;

  hMultV0=nullptr; //Dobrin
  for (int i = 0; i < 2; ++i)  hQx2mV0[i] = nullptr;
  for (int i = 0; i < 2; ++i)  hQy2mV0[i] = nullptr;
  for (int i = 0; i < 64; ++i) fMultV0Ch[i] = -999.;
  for (int i = 0; i < 3; ++i)  fV0XMean[i]  = -999.;
  for (int i = 0; i < 3; ++i)  fV0YMean[i]  = -999.;

  for (int i = 0; i < 2; ++i) hCent[i]   = nullptr;
  for (int i = 0; i < 2; ++i) hVz[i]     = nullptr;

  for (int i = 0; i < 8; ++i) hCentQA[i]     = nullptr;
  for (int i = 0; i < 2; ++i) hMultCentQA[i] = nullptr;
  for (int i = 0; i < 6; ++i) hMultMultQA[i] = nullptr;

  for (int i = 0; i < 2; ++i) hEta[i]    = nullptr;
  for (int i = 0; i < 2; ++i) hPhi[i]    = nullptr;
  for (int i = 0; i < 2; ++i) hEtaPhi[i] = nullptr;
  for (int i = 0; i < 2; ++i) hDcaXy[i]  = nullptr;
  for (int i = 0; i < 2; ++i) hDcaZ[i]   = nullptr;
  for (int i = 0; i < 2; ++i) hNhits[i]  = nullptr;

  for (int i = 0; i < 3; ++i) hQxCentRecenter[i] = nullptr;
  for (int i = 0; i < 3; ++i) hQxVtxRecenter[i]  = nullptr;
  for (int i = 0; i < 3; ++i) hQyCentRecenter[i] = nullptr;
  for (int i = 0; i < 3; ++i) hQyVtxRecenter[i]  = nullptr;
  for (int i = 0; i < 3; ++i) hQnCentRecenter[i] = nullptr;
  for (int i = 0; i < 10; ++i) for (int j = 0; j < 3; ++j) hPsiV0Recenter[i][j] = nullptr;

  for (int i = 0; i < 2; i++) {
    fHistLambdaPt[i]                  = nullptr;            
    fHistLambdaEta[i]                 = nullptr;
    fHistLambdaPhi[i]                 = nullptr;
    fHistLambdaDcaToPrimVertex[i]     = nullptr;
    fHistLambdaCPA[i]                 = nullptr;
    fHistLambdaDecayLength[i]         = nullptr;
    fHistLambdaMass[i]                = nullptr;
    fHistAntiLambdaPt[i]              = nullptr;
    fHistAntiLambdaEta[i]             = nullptr;
    fHistAntiLambdaPhi[i]             = nullptr;
    fHistAntiLambdaDcaToPrimVertex[i] = nullptr;
    fHistAntiLambdaCPA[i]             = nullptr;
    fHistAntiLambdaDecayLength[i]     = nullptr;
    fHistAntiLambdaMass[i]            = nullptr;
    fProfileLambdaMassVsPt[i]         = nullptr;
    fProfileAntiLambdaMassVsPt[i]     = nullptr;
  }  

  for (int i = 0; i < 3; i++) {
    fHist3DdNdPhiCentPthPos[i] = nullptr;
    fHist3DdNdPhiCentPthNeg[i] = nullptr;  
    fHist3DdNdPhiCentPtProton[i] = nullptr;
    fHist3DdNdPhiCentPtAntiProton[i] = nullptr;
  }
  for (int i = 0; i < 4; i++) {
    fHist3DdNdPhiCentPtLambda[i] = nullptr;
    fHist3DdNdPhiCentPtAntiLambda[i] = nullptr;
  }

  DefineInput(0,TChain::Class());
  DefineOutput(1,TList::Class());

  int inputslot = 1;
  if (fPeriod.EqualTo("LHC10h")){
    if (fDoNUE) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    }
    if (fDoNUA) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    }
    if (fV0CalibOn) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    } 
  } 
  if (fPeriod.EqualTo("LHC15o")){
    if (fDoNUE) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    }
    if (fDoNUA) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    }
    if (fV0CalibOn) {
      DefineInput(inputslot, TList::Class());
      inputslot++;
    } 
  }
}

  //------------------------------------------------

AliAnalysisTaskLambdaProtonCVE::~AliAnalysisTaskLambdaProtonCVE()
{
  // Destructor
  // histograms are in the output list and deleted when the output
  if (fOutputList) delete fOutputList;
}

//_____________________________________________________________________________

void AliAnalysisTaskLambdaProtonCVE::Terminate(Option_t *)
{
  // Terminate loop
  Printf("Terminate");
}

//---------------------------------------------------

void AliAnalysisTaskLambdaProtonCVE::UserCreateOutputObjects()
{
  fOutputList = new TList();
  fOutputList->SetName(GetName());
  fOutputList->SetOwner(kTRUE);

  //------------------
  // Info
  // ------------------
  if (fPeriod.EqualTo("LHC10h") ){
      TString runNumList[90]={
        "139510","139507","139505","139503","139465","139438","139437","139360","139329","139328","139314","139310",
        "139309","139173","139107","139105","139038","139037","139036","139029","139028","138872","138871","138870",
        "138837","138732","138730","138666","138662","138653","138652","138638","138624","138621","138583","138582",
        "138579","138578","138534","138469","138442","138439","138438","138396","138364","138275","138225","138201",
        "138197","138192","138190","137848","137844","137752","137751","137724","137722","137718","137704","137693",
        "137692","137691","137686","137685","137639","137638","137608","137595","137549","137546","137544","137541",
        "137539","137531","137530","137443","137441","137440","137439","137434","137432","137431","137430","137243",
        "137236","137235","137232","137231","137162","137161"};
      hRunNumBin = new TH1I("runNumBin","",100,0,100);
      for (int i=0; i<90; ++i){    
        hRunNumBin->GetXaxis()->SetBinLabel(i+1,runNumList[i].Data());
      }
      fOutputList->Add(hRunNumBin);
  } else if (fPeriod.EqualTo("LHC11h") ){
      TString runNumList[39]={
        "170387","170040","170268","170228","170207","169838","170159","170204","170311","170084",
        "169835","170088","170593","170203","170270","169846","170163","170388","170155","170083",
        "170572","169837","169855","170306","170269","170089","170309","170091","170081","170230",
        "170085","170315","170027","170193","170312","170313","170308","169858","169859"};
      hRunNumBin = new TH1I("runNumBin","",100,0,100);
      for (int i=0; i<39; ++i){    
        hRunNumBin->GetXaxis()->SetBinLabel(i+1,runNumList[i].Data());
      }
      fOutputList->Add(hRunNumBin);
  } else if (fPeriod.EqualTo("LHC15o") ){
      TString runNumList[138]={
       "246994","246991","246989","246984","246982","246948","246945","246928","246871","246870","246867","246865", 
       "246864","246859","246858","246851","246847","246846","246845","246844","246810","246809","246808","246807", 
       "246805","246804","246766","246765","246763","246760","246759","246758","246757","246751","246750","246434", 
       "246431","246424","246392","246391","246276","246275","246272","246271","246225","246222","246217","246185", 
       "246182","246181","246180","246178","246153","246152","246151","246148","246115","246113","246089","246087", 
       "246053","246052","246049","246048","246042","246037","246036","246012","246003","246001","245963","245954", 
       "245952","245949","245923","245833","245831","245829","245793","245785","245775","245766","245759","245752", 
       "245731","245729","245705","245702","245692","245683","245554","245545","245544","245543","245542","245540", 
       "245535","245507","245505","245504","245501","245497","245496","245454","245453","245450","245446","245441", 
       "245411","245410","245409","245407","245401","245397","245396","245353","245349","245347","245346","245345", 
       "245343","245259","245233","245232","245231","245152","245151","245146","245145","245068","245066","245064", 
       "244983","244982","244980","244975","244918","244917"};
      hRunNumBin = new TH1I("runNumBin","",150,0,150);
      for (int i=0; i<138; ++i){    
        hRunNumBin->GetXaxis()->SetBinLabel(i+1,runNumList[i].Data());
      }
      fOutputList->Add(hRunNumBin);
  }

  // Copy TList
  Int_t inSlotCounter=1;
  if(fDoNUE) {
    if (fPeriod.EqualTo("LHC11h") || fPeriod.EqualTo("LHC10h") ) {
      fListNUE = (TList*) GetInputData(inSlotCounter);
      if (fDebug) fListNUE->ls();
      inSlotCounter++;
      if (!fListNUE) {
        AliError(Form("%s: Wrong NUE file Run1.", GetName()));
        return;
      };
    }
    else if (fPeriod.EqualTo("LHC15o")){
      fListNUE = (TList*) GetInputData(inSlotCounter);
      inSlotCounter++;
      if (!fListNUE) {
        AliError(Form("%s: Wrong NUE file 15o.", GetName()));
        return;
      };     
    }
  }

  if(fDoNUA) {
    if (fPeriod.EqualTo("LHC10h") ) {
      fListNUA = (TList*) GetInputData(inSlotCounter);
      if (fDebug) fListNUA->ls();
      inSlotCounter++;
      if (!fListNUA) {
        AliError(Form("%s: Wrong NUA file 10h.", GetName()));
        return;
      };
    } else if (fPeriod.EqualTo("LHC11h") ){
      fListNUA = (TList*) GetInputData(inSlotCounter);
      inSlotCounter++;
      if (!fListNUA) {        
        AliError(Form("%s: Wrong NUA file 11h.", GetName()));
        return;
      }
    } else if (fPeriod.EqualTo("LHC15o") ){ //Rihan's NUA
      fListNUA = (TList*) GetInputData(inSlotCounter);
      if (fDebug) fListNUA->ls();
      inSlotCounter++;
      if (!fListNUA) {        
        AliError(Form("%s: Wrong NUA file 15o2.", GetName()));
        return;
      }
    } 
  }

  // Qn Calib
  if (fV0CalibOn){
      if (fPeriod.EqualTo("LHC10h") ) {
        fListVZEROCALIB = (TList*) GetInputData(inSlotCounter);
        if (fDebug) fListVZEROCALIB->ls();
        inSlotCounter++;
        if (!fListVZEROCALIB) {
          AliError(Form("%s: Wrong V0 Calib file 10h.", GetName()));
          return;
        };

        // Read GE Hists (x_y) : (iCh_runnumBin)
        hMultV0Read = (TH2D*)fListVZEROCALIB->FindObject("hMultV0");
        // Read Qx/y Mean Hists (x_y_z) : (runnumBin_centBin_vzBin)
        pV0XMeanRead[1] = (TProfile3D*)fListVZEROCALIB->FindObject("pV0CCosMean");
        pV0YMeanRead[1] = (TProfile3D*)fListVZEROCALIB->FindObject("pV0CSinMean");
        pV0XMeanRead[2] = (TProfile3D*)fListVZEROCALIB->FindObject("pV0ACosMean");
        pV0YMeanRead[2] = (TProfile3D*)fListVZEROCALIB->FindObject("pV0ASinMean");
      }
  }

  //------------------
  // QA
  //------------------
  // event-wise
  hEvtCount = new TH1D("hEvtCount", "Event Count", 25, 1, 26);
  hEvtCount->GetXaxis()->SetBinLabel(1,"all");
  hEvtCount->GetXaxis()->SetBinLabel(2,"readin");
  hEvtCount->GetXaxis()->SetBinLabel(3,"evt");
  hEvtCount->GetXaxis()->SetBinLabel(4,"runNum");
  hEvtCount->GetXaxis()->SetBinLabel(5,"vertex");
  hEvtCount->GetXaxis()->SetBinLabel(6,"centrality");
  hEvtCount->GetXaxis()->SetBinLabel(7,"pileup");
  hEvtCount->GetXaxis()->SetBinLabel(8,"getVZEROplane");
  hEvtCount->GetXaxis()->SetBinLabel(9,"looptrack");
  hEvtCount->GetXaxis()->SetBinLabel(10,"resolution");
  hEvtCount->GetXaxis()->SetBinLabel(11,"loopV0");
  hEvtCount->GetXaxis()->SetBinLabel(12,"pair");
  hEvtCount->GetXaxis()->SetBinLabel(20,"manager");
  hEvtCount->GetXaxis()->SetBinLabel(21,"handler");
  hEvtCount->GetXaxis()->SetBinLabel(22,"fAOD");
  hEvtCount->GetXaxis()->SetBinLabel(23,"fPID");
  hEvtCount->GetXaxis()->SetBinLabel(24,"fUtils");
  hEvtCount->GetXaxis()->SetBinLabel(25,"fMultSel");
  fOutputList->Add(hEvtCount);

  hCent[0] = new TH1D("hCentBefCut", "", 100, 0., 100.);
  hCent[1] = new TH1D("hCentAftCut", "", 100, 0., 100.);
  fOutputList->Add(hCent[0]);
  fOutputList->Add(hCent[1]);

  hVz[0] = new TH1D("hVzBeforeCut", "", 200, -50., 50.);
  hVz[1] = new TH1D("hVzAfterCut",  "", 200, -50., 50.);
  fOutputList->Add(hVz[0]);
  fOutputList->Add(hVz[1]);

  hCentQA[0] = new TH2D("hCentQAV0MSPD1BefCut", ";centV0M;centSPD1", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[0]);
  hCentQA[1] = new TH2D("hCentQAV0MSPD1AftCut", ";centV0M;centSPD1", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[1]);

  hCentQA[2] = new TH2D("hCentQAV0MTRKBefCut", ";centV0M;centTRK", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[2]);
  hCentQA[3] = new TH2D("hCentQAV0MTRKAftCut", ";centV0M;centTRK", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[3]);

  hCentQA[4] = new TH2D("hCentQAV0MSPD0BefCut", ";centV0M;centSPD0", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[4]);
  hCentQA[5] = new TH2D("hCentQAV0MSPD0AftCut", ";centV0M;centSPD0", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[5]);

  hCentQA[6] = new TH2D("hCentQASPD1SPD0BefCut", ";centSPD1;centSPD0", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[6]);
  hCentQA[7] = new TH2D("hCentQASPD1SPD0AftCut", ";centSPD1;centSPD0", 100, 0, 100, 100, 0, 100);
  fOutputList->Add(hCentQA[7]);

  hMultCentQA[0] = new TH2D("hMultCentQABefCut", ";centV0M;multFB32", 100, 0, 100, 20, 0, 5000);
  hMultCentQA[1] = new TH2D("hMultCentQAAftCut", ";centV0M;multFB32", 100, 0, 100, 20, 0, 5000);
  fOutputList->Add(hMultCentQA[0]);
  fOutputList->Add(hMultCentQA[1]);

  // if (fMultComp.EqualTo("pileupByEDSTPC128") || fMultComp.EqualTo("pileupByGlobalTPC1")){
  //   hMultMultQA[0] = new TH2D("hMultMultQAmTPCmESDPileupBefCut", "befCut;multTPC;multESD", 50, 0, 5000, 160, 0, 16000);
  //   hMultMultQA[1] = new TH2D("hMultMultQAmClobalmTPCEFPileupBefCut", "befCut;multGlobal;multTPCFE", 50, 0, 5000, 50, 0, 5000);
  //   hMultMultQA[2] = new TH2D("hMultMultQAmFB32mTrkTOFBefCut", "befCut;multTrkTOF;nTrk", 201, 0, 20000, 201, 0, 20000);
  //   hMultMultQA[3] = new TH2D("hMultMultQAmTPCmESDPileupAftCut", "aftCut;multTPC;multESD", 50, 0, 5000, 160, 0, 16000);
  //   hMultMultQA[4] = new TH2D("hMultMultQAmClobalmTPCEFPileupAftCut", "aftCut;multGlobal;multTPCFE", 50, 0, 5000, 50, 0, 5000);
  //   hMultMultQA[5] = new TH2D("hMultMultQAmFB32mTrkTOFAftCut", "aftCut;multTrkTOF;nTrk", 201, 0, 20000, 201, 0, 20000);
  //   fOutputList->Add(hMultMultQA[0]);
  //   fOutputList->Add(hMultMultQA[1]);
  //   fOutputList->Add(hMultMultQA[2]);
  //   fOutputList->Add(hMultMultQA[3]);
  //   fOutputList->Add(hMultMultQA[4]);
  //   fOutputList->Add(hMultMultQA[5]);
  // }


  // track-wise
  hPt = new TH1D("hPt", "", 200, 0., 20.);
  fOutputList->Add(hPt);
  hEta[0] = new TH1D("hEtaBeforeCut", "", 200, -10., 10.);
  hEta[1] = new TH1D("hEtaAfterCut",  "", 200, -10., 10.);
  fOutputList->Add(hEta[0]);
  fOutputList->Add(hEta[1]);
  hPhi[0] = new TH1D("hPhiBeforeCor", "", 50, 0, 6.283185);
  hPhi[1] = new TH1D("hPhiAfterCor", "", 50, 0, 6.283185);
  fOutputList->Add(hPhi[0]);
  fOutputList->Add(hPhi[1]);
  hEtaPhi[0] = new TH2D("hEtaPhiBeforeCor", "", 50, 0, 6.283185, 16,-0.8,0.8);
  hEtaPhi[1] = new TH2D("hEtaPhiAfterCor", "", 50, 0, 6.283185, 16,-0.8,0.8);
  fOutputList->Add(hEtaPhi[0]);
  fOutputList->Add(hEtaPhi[1]);
  hNhits[0] = new TH1D("hNhitsBeforeCut", "", 200, 0., 200.);
  hNhits[1] = new TH1D("hNhitsAfterCut",  "", 200, 0., 200.);
  fOutputList->Add(hNhits[0]);
  fOutputList->Add(hNhits[1]);
  hPDedx = new TH2D("hPDedx", "", 400, -10., 10., 400, 0, 1000);
  fOutputList->Add(hPDedx);
  if (fPeriod.EqualTo("LHC11h") || fPeriod.EqualTo("LHC10h")){
    hDcaXy[0] = new TH1D("hDcaXyBeforeCut", "", 100, 0., 10.);
    hDcaXy[1] = new TH1D("hDcaXyAfterCut",  "", 100, 0., 10.);
    fOutputList->Add(hDcaXy[0]);
    fOutputList->Add(hDcaXy[1]);
    hDcaZ[0] = new TH1D("hDcaZBeforeCut", "", 100, 0., 10.);
    hDcaZ[1] = new TH1D("hDcaZAfterCut",  "", 100, 0., 10.);
    fOutputList->Add(hDcaZ[0]);
    fOutputList->Add(hDcaZ[1]);
  }

  if (fQAV0){
    hQnCentRecenter[0] = new TH2D("hqnV0MRecenter","",100, 0, 100, 570, 0, 12); 
    hQnCentRecenter[1] = new TH2D("hqnV0CRecenter","",100, 0, 100, 570, 0, 12); 
    hQnCentRecenter[2] = new TH2D("hqnV0ARecenter","",100, 0, 100, 570, 0, 12); 
    //fOutputList->Add(hQnCentRecenter[0]);
    fOutputList->Add(hQnCentRecenter[1]);
    fOutputList->Add(hQnCentRecenter[2]); 
    hQxCentRecenter[0] = new TH2D("hqxRecenterV0MvsCentSPD","",100, 0, 100, 32, -600, 600);
    hQxCentRecenter[1] = new TH2D("hqxRecenterV0CvsCentSPD","",100, 0, 100, 32, -600, 600);
    hQxCentRecenter[2] = new TH2D("hqxRecenterV0AvsCentSPD","",100, 0, 100, 32, -600, 600);
    hQyCentRecenter[0] = new TH2D("hqyRecenterV0MvsCentSPD","",100, 0, 100, 32, -600, 600);
    hQyCentRecenter[1] = new TH2D("hqyRecenterV0CvsCentSPD","",100, 0, 100, 32, -600, 600);
    hQyCentRecenter[2] = new TH2D("hqyRecenterV0AvsCentSPD","",100, 0, 100, 32, -600, 600);
    for (int i = 1; i < 3; ++i) fOutputList->Add(hQxCentRecenter[i]);
    for (int i = 1; i < 3; ++i) fOutputList->Add(hQyCentRecenter[i]); 
    hQxVtxRecenter[0] = new TH2D("hqxRecenterV0MvsVz","",20, -10, 10, 32, -600, 600);
    hQxVtxRecenter[1] = new TH2D("hqxRecenterV0CvsVz","",20, -10, 10, 32, -600, 600);
    hQxVtxRecenter[2] = new TH2D("hqxRecenterV0AvsVz","",20, -10, 10, 32, -600, 600);
    hQyVtxRecenter[0] = new TH2D("hqyRecenterV0MvsVz","",20, -10, 10, 32, -600, 600);
    hQyVtxRecenter[1] = new TH2D("hqyRecenterV0CvsVz","",20, -10, 10, 32, -600, 600);
    hQyVtxRecenter[2] = new TH2D("hqyRecenterV0AvsVz","",20, -10, 10, 32, -600, 600);
    for (int i = 1; i < 3; ++i) fOutputList->Add(hQxVtxRecenter[i]); 
    for (int i = 1; i < 3; ++i) fOutputList->Add(hQyVtxRecenter[i]);
    for (int iCent = 0; iCent < 10; ++iCent){
      hPsiV0Recenter[iCent][0] = new TH1D(Form("hpsiV0MRecenterCent%i", iCent),"", 360, 0., TMath::TwoPi());
      hPsiV0Recenter[iCent][1] = new TH1D(Form("hpsiV0CRecenterCent%i", iCent),"", 360, 0., TMath::TwoPi());
      hPsiV0Recenter[iCent][2] = new TH1D(Form("hpsiV0ARecenterCent%i", iCent),"", 360, 0., TMath::TwoPi());
    } 
    for (int iCent = 0; iCent < 10; ++iCent){
      for (int i = 1; i < 3; ++i) fOutputList->Add(hPsiV0Recenter[iCent][i]);    
    } 
  }

  ///TPC Event Plane Correlations for Resolution Estimation
  hTPCPsi2Correlation = new TProfile("hTPCPsi2Correlation","TPCPos-TPCNeg Psi2 Res. vs Cent; Cent; Resolution",90,0,90);
  ///V0X-V0X/TPC  Event Plane Correlations for Resolution:
  hV0CV0APsi2Correlation = new TProfile("hV0CV0APsi2Correlation","V0C-V0A Psi2; Cent; Resolution",90,0,90);
  hV0CTPCPosPsi2Correlation = new TProfile("hV0CTPCPosPsi2Correlation","V0C-TPCPos Psi2; Cent; Resolution",90,0,90);
  hV0ATPCPosPsi2Correlation = new TProfile("hV0ATPCPosPsi2Correlation","V0A-TPCPos Psi2; Cent; Resolution",90,0,90);
  hV0CTPCNegPsi2Correlation = new TProfile("hV0CTPCNegPsi2Correlation","V0C-TPCNeg Psi2; Cent; Resolution",90,0,90);
  hV0ATPCNegPsi2Correlation = new TProfile("hV0ATPCNegPsi2Correlation","V0C-TPCNeg Psi2; Cent; Resolution",90,0,90);
  fOutputList->Add(hTPCPsi2Correlation);
  fOutputList->Add(hV0CV0APsi2Correlation);
  fOutputList->Add(hV0CTPCPosPsi2Correlation);
  fOutputList->Add(hV0ATPCPosPsi2Correlation);
  fOutputList->Add(hV0CTPCNegPsi2Correlation);
  fOutputList->Add(hV0ATPCNegPsi2Correlation);
  
  //------------------
  // physics
  //------------------

  /////////   LAMBDA Histograms   //////////
  /////--------> chunzheng: V0 QA and other histograms:
  //V0-mother informations:
  fHistV0Pt = new TH1D("hV0Pt","", 200, 0., 20.);
  fOutputList->Add(fHistV0Pt);
  fHistV0Eta = new TH1D("hV0Eta","", 200, -10., 10.);
  fOutputList->Add(fHistV0Eta);
  fHistV0DcatoPrimVertex = new TH1D("hV0DcaToPrimVertex","",200, 0., 20.);
  fOutputList->Add(fHistV0DcatoPrimVertex);
  fHistV0CPA = new TH1D("hV0CPA","", 1000, 0.9, 1.);
  fOutputList->Add(fHistV0CPA);
  fHistV0DecayLength = new TH1D("hV0DecayLength","",500,0,500.);
  fOutputList->Add(fHistV0DecayLength);

  Char_t name[10];
  for(int i=0; i<2; i++){
    ///// Case 0 = before cut, case 1 = afterCut.
    if(i==0) sprintf(name,"Before");
    else     sprintf(name,"After");
    /// Lambdas:
    fHistLambdaPt[i] = new TH1D(Form("hLambdaPt_%sMassCut",name),"", 200, 0., 20.);
    fOutputList->Add(fHistLambdaPt[i]);
    fHistLambdaEta[i] = new TH1D(Form("hLambdaEta_%sMassCut",name),"",200, -10., 10.);
    fOutputList->Add(fHistLambdaEta[i]);
    fHistLambdaPhi[i] = new TH1D(Form("hLambdaPhi_%sMassCut",name),"", 360, 0., TMath::TwoPi());
    fOutputList->Add(fHistLambdaPhi[i]);
    fHistLambdaDcaToPrimVertex[i] = new TH1D(Form("hLambdaDcaToPrimVertex_%sMassCut",name),"",200, 0., 20.);
    fOutputList->Add(fHistLambdaDcaToPrimVertex[i]);
    fHistLambdaCPA[i] = new TH1D(Form("hLambdaCPA_%sMassCut",name),"",200, 0.9, 1.);
    fOutputList->Add(fHistLambdaCPA[i]);
    fHistLambdaDecayLength[i] = new TH1D(Form("hLambdaDecayLength_%sMassCut",name),"", 250, 0., 500.);
    fOutputList->Add(fHistLambdaDecayLength[i]);
    fHistLambdaMass[i] = new TH1D(Form("hLambdaMass_%sMassCut",name),"",1000,1.,1.25); //  Current bin size = 0.00025
    fOutputList->Add(fHistLambdaMass[i]);
    fProfileLambdaMassVsPt[i] = new TProfile(Form("pLambdaMassVsPt_%sMassCut",name),"",200,0,20);
    fOutputList->Add(fProfileLambdaMassVsPt[i]);

    // AntiLambdas
    fHistAntiLambdaPt[i] = new TH1D(Form("hAntiLambdaPt_%sMassCut",name),"", 200, 0., 20.);
    fOutputList->Add(fHistAntiLambdaPt[i]);
    fHistAntiLambdaEta[i] = new TH1D(Form("hAntiLambdaEta_%sMassCut",name),"",200, -10., 10.);
    fOutputList->Add(fHistAntiLambdaEta[i]);
    fHistAntiLambdaPhi[i] = new TH1D(Form("hAntiLambdaPhi_%sMassCut",name),"", 360, 0, TMath::TwoPi());
    fOutputList->Add(fHistAntiLambdaPhi[i]);
    fHistAntiLambdaDcaToPrimVertex[i] = new TH1D(Form("hAntiLambdaDcaToPrimVertex_%sMassCut",name),"",200, 0., 20.);
    fOutputList->Add(fHistAntiLambdaDcaToPrimVertex[i]);
    fHistAntiLambdaCPA[i] = new TH1D(Form("hAntiLambdaCPA_%sMassCut",name),"",200, 0.9, 1.);
    fOutputList->Add(fHistAntiLambdaCPA[i]);
    fHistAntiLambdaDecayLength[i] = new TH1D(Form("hAntiLambdaDecayLength_%sMassCut",name),"", 250, 0., 500.);
    fOutputList->Add(fHistAntiLambdaDecayLength[i]);
    fHistAntiLambdaMass[i] = new TH1D(Form("hAntiLambdaMass_%sMassCut",name),"",1000,1.,1.25); // Current bin size = 0.00025
    fOutputList->Add(fHistAntiLambdaMass[i]);
    fProfileAntiLambdaMassVsPt[i] = new TProfile(Form("pAntiLambdaMassVsPt_%sMassCut",name),"",200,0,20);
    fOutputList->Add(fProfileAntiLambdaMassVsPt[i]);    
  }


  ///Gamma Correlators:
  //TPC Plane
  ///Lambda - X
  fProfileGammaTPC_Lambda_hPos = new TProfile("fProfileGammaTPC_Lambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_Lambda_hPos);
  fProfileGammaTPC_Lambda_hNeg = new TProfile("fProfileGammaTPC_Lambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_Lambda_hNeg);
  fProfileGammaTPC_Lambda_Proton = new TProfile("fProfileGammaTPC_Lambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_Lambda_Proton);
  fProfileGammaTPC_Lambda_AntiProton = new TProfile("fProfileGammaTPC_Lambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaTPC_Lambda_AntiProton);

  ///AntiLambda - X
  fProfileGammaTPC_AntiLambda_hPos = new TProfile("fProfileGammaTPC_AntiLambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_AntiLambda_hPos);
  fProfileGammaTPC_AntiLambda_hNeg = new TProfile("fProfileGammaTPC_AntiLambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_AntiLambda_hNeg);
  fProfileGammaTPC_AntiLambda_Proton = new TProfile("fProfileGammaTPC_AntiLambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaTPC_AntiLambda_Proton);
  fProfileGammaTPC_AntiLambda_AntiProton = new TProfile("fProfileGammaTPC_AntiLambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaTPC_AntiLambda_AntiProton);

  //V0C Plane
  ///Lambda - X
  fProfileGammaV0C_Lambda_hPos = new TProfile("fProfileGammaV0C_Lambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_Lambda_hPos);
  fProfileGammaV0C_Lambda_hNeg = new TProfile("fProfileGammaV0C_Lambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_Lambda_hNeg);
  fProfileGammaV0C_Lambda_Proton = new TProfile("fProfileGammaV0C_Lambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_Lambda_Proton);
  fProfileGammaV0C_Lambda_AntiProton = new TProfile("fProfileGammaV0C_Lambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaV0C_Lambda_AntiProton);

  ///AntiLambda - X
  fProfileGammaV0C_AntiLambda_hPos = new TProfile("fProfileGammaV0C_AntiLambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_AntiLambda_hPos);
  fProfileGammaV0C_AntiLambda_hNeg = new TProfile("fProfileGammaV0C_AntiLambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_AntiLambda_hNeg);
  fProfileGammaV0C_AntiLambda_Proton = new TProfile("fProfileGammaV0C_AntiLambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0C_AntiLambda_Proton);
  fProfileGammaV0C_AntiLambda_AntiProton = new TProfile("fProfileGammaV0C_AntiLambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaV0C_AntiLambda_AntiProton);

  //V0A Plane
  ///Lambda - X
  fProfileGammaV0A_Lambda_hPos = new TProfile("fProfileGammaV0A_Lambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_Lambda_hPos);
  fProfileGammaV0A_Lambda_hNeg = new TProfile("fProfileGammaV0A_Lambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_Lambda_hNeg);
  fProfileGammaV0A_Lambda_Proton = new TProfile("fProfileGammaV0A_Lambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_Lambda_Proton);
  fProfileGammaV0A_Lambda_AntiProton = new TProfile("fProfileGammaV0A_Lambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaV0A_Lambda_AntiProton);

  ///AntiLambda - X
  fProfileGammaV0A_AntiLambda_hPos = new TProfile("fProfileGammaV0A_AntiLambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_AntiLambda_hPos);
  fProfileGammaV0A_AntiLambda_hNeg = new TProfile("fProfileGammaV0A_AntiLambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_AntiLambda_hNeg);
  fProfileGammaV0A_AntiLambda_Proton = new TProfile("fProfileGammaV0A_AntiLambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileGammaV0A_AntiLambda_Proton);
  fProfileGammaV0A_AntiLambda_AntiProton = new TProfile("fProfileGammaV0A_AntiLambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileGammaV0A_AntiLambda_AntiProton);
  
  ///Delta Correlators:
   ///Lambda - X
  fProfileDelta_Lambda_hPos = new TProfile("fProfileDelta_Lambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_Lambda_hPos);
  fProfileDelta_Lambda_hNeg = new TProfile("fProfileDelta_Lambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_Lambda_hNeg);
  fProfileDelta_Lambda_Proton = new TProfile("fProfileDelta_Lambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_Lambda_Proton);
  fProfileDelta_Lambda_AntiProton = new TProfile("fProfileDelta_Lambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileDelta_Lambda_AntiProton);

  ///AntiLambda - X
  fProfileDelta_AntiLambda_hPos = new TProfile("fProfileDelta_AntiLambda_hPos", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_AntiLambda_hPos);
  fProfileDelta_AntiLambda_hNeg = new TProfile("fProfileDelta_AntiLambda_hNeg", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_AntiLambda_hNeg);
  fProfileDelta_AntiLambda_Proton = new TProfile("fProfileDelta_AntiLambda_Proton", "", 18, 0., 90.);
  fOutputList->Add(fProfileDelta_AntiLambda_Proton);
  fProfileDelta_AntiLambda_AntiProton = new TProfile("fProfileDelta_AntiLambda_AntiProton", "", 18, 0., 90.);  
  fOutputList->Add(fProfileDelta_AntiLambda_AntiProton);



  // Dobrin 15o pass2
  if (fPeriod.EqualTo("LHC15o")){
    fSPDCutPU = new TF1("fSPDCutPU", "450. + 3.9*x", 0, 50000);
      
    Double_t parV0[8] = {33.4237, 0.953516, 0.0712137, 227.923, 8.9239, -0.00319679, 0.000306314, -7.6627e-07};
    fV0CutPU = new TF1("fV0CutPU", "[0]+[1]*x - 6.*[2]*([3] + [4]*sqrt(x) + [5]*x + [6]*x*sqrt(x) + [7]*x*x)", 0, 100000);
    fV0CutPU->SetParameters(parV0);
      
    Double_t parV0CL0[6] = {0.0193587, 0.975914, 0.675714, 0.0292263, -0.000549509, 5.86421e-06};
    fCenCutLowPU = new TF1("fCenCutLowPU", "[0]+[1]*x - 5.5*([2]+[3]*x+[4]*x*x+[5]*x*x*x)", 0, 100);
    fCenCutLowPU->SetParameters(parV0CL0);
    fCenCutHighPU = new TF1("fCenCutHighPU", "[0]+[1]*x + 5.5*([2]+[3]*x+[4]*x*x+[5]*x*x*x)", 0, 100);
    fCenCutHighPU->SetParameters(parV0CL0);
      
    Double_t parFB32[9] = {-812.822, 6.41796, 5421.83, -0.382601, 0.0299686, -26.6249, 321.388, -0.82615, 0.0167828};
    fMultCutPU = new TF1("fMultCutPU", "[0]+[1]*x+[2]*exp([3]-[4]*x) - 6.*([5]+[6]*exp([7]-[8]*x))", 0, 100);
    fMultCutPU->SetParameters(parFB32);
  }

  if (fPeriod.EqualTo("LHC18q")){
    // Rihan Pile-up function 18
    fSPDCutPU = new TF1("fSPDCutPU", "400. + 4.*x", 0, 10000);

    Double_t parV0[8] = {43.8011, 0.822574, 8.49794e-02, 1.34217e+02, 7.09023e+00, 4.99720e-02, -4.99051e-04, 1.55864e-06};
    fV0CutPU  = new TF1("fV0CutPU", "[0]+[1]*x - 6.*[2]*([3] + [4]*sqrt(x) + [5]*x + [6]*x*sqrt(x) + [7]*x*x)", 0, 100000);
    fV0CutPU->SetParameters(parV0);
    
    Double_t parV0CL0[6] = {0.320462, 0.961793, 1.02278, 0.0330054, -0.000719631, 6.90312e-06};
    fCenCutLowPU  = new TF1("fCenCutLowPU", "[0]+[1]*x - 6.5*([2]+[3]*x+[4]*x*x+[5]*x*x*x)", 0, 100);
    fCenCutLowPU->SetParameters(parV0CL0);
    fCenCutHighPU = new TF1("fCenCutHighPU", "[0]+[1]*x + 5.5*([2]+[3]*x+[4]*x*x+[5]*x*x*x)", 0, 100);
    fCenCutHighPU->SetParameters(parV0CL0);

    Double_t parFB32[8] = {2093.36, -66.425, 0.728932, -0.0027611, 1.01801e+02, -5.23083e+00, -1.03792e+00, 5.70399e-03};
    fMultCutPU = new TF1("fMultCutPU", "[0]+[1]*x+[2]*x*x+[3]*x*x*x - 6.*([4]+[5]*sqrt(x)+[6]*x+[7]*x*x)", 0, 90);
    fMultCutPU->SetParameters(parFB32);
  }

  PostData(1,fOutputList); 
  if (fDebug) Printf("Post Data Success!");
}
//------------------------------------------------
//------------------------------------------------

void AliAnalysisTaskLambdaProtonCVE::UserExec(Option_t *)
{
  hEvtCount->Fill(1);
  AliAnalysisManager* manager = AliAnalysisManager::GetAnalysisManager();
  if (!manager) {
    AliError(Form("%s: Could not get Analysis Manager", GetName()));
  } else hEvtCount->Fill(20);
  AliAODInputHandler* handler = (AliAODInputHandler*)manager->GetInputEventHandler();
  if (!handler) {
    AliError(Form("%s: Could not get Input Handler", GetName()));
  } else hEvtCount->Fill(21);
  fAOD = dynamic_cast <AliAODEvent*> (InputEvent());
  if (!fAOD) {
    AliError(Form("%s: Could not get AOD event", GetName()));
  } else hEvtCount->Fill(22);
  fPIDResponse = handler->GetPIDResponse();
  if (!fPIDResponse) {
    AliError(Form("%s: Could not get PIDResponse", GetName()));
  } else hEvtCount->Fill(23);
  fUtils = new AliAnalysisUtils();
  if (!fUtils) {
    AliError(Form("%s: Could not get AliAnalysisUtils", GetName()));
  } else hEvtCount->Fill(24);
  if (fPeriod.EqualTo("LHC15o")){
    AliMultSelection* fMultSel = (AliMultSelection*)InputEvent()->FindListObject("MultSelection");
    if (!fMultSel) {
      AliError(Form("%s: Could not get AliMultSelection", GetName()));
    } else hEvtCount->Fill(25);
    if (!manager || !handler || !fAOD || !fPIDResponse || !fUtils || !fMultSel) return;
  }
  else if (!manager || !handler || !fAOD || !fPIDResponse || !fUtils) return;
  hEvtCount->Fill(2);
  if (fDebug) Printf("Info done!");

  //----------------------------
  // Trigger
  //----------------------------
  UInt_t mask = handler->IsEventSelected();
  bool isTrigselected = false;
  if (fTrigger.EqualTo("kINT7"))    isTrigselected = mask&AliVEvent::kINT7; //run 2
  else if (fTrigger.EqualTo("kMB")) isTrigselected = mask&AliVEvent::kMB;   //10h
  else if (fTrigger.EqualTo("kMB+kCentral+kSemiCentral")) 
  isTrigselected = mask&AliVEvent::kMB+AliVEvent::kCentral+AliVEvent::kSemiCentral; //11h
  if(isTrigselected == false) return;
  hEvtCount->Fill(3);
  if (fDebug) Printf("trigger done!");

  //----------------------------
  // event-wise selection
  //----------------------------
  // run number
  Int_t run = fAOD->GetRunNumber();
  if (run < 200000 && fPeriod.EqualTo("LHC15o")) return;
  if (run > 200000 && fPeriod.EqualTo("LHC11h")) return;
  if(run != fRunNum){
      // Load the calibrations run dependent
      if (fPeriod.EqualTo("LHC15o")) OpenInfoCalibration(run);
      fRunNum = run;
      fRunNumBin = GetRunNumBin(fRunNum);
      if (fRunNumBin<0) return;
  } 
  hRunNumBin->Fill(fRunNumBin);
  hEvtCount->Fill(4);
  if (fDebug) Printf("run nummbr done!");

  // vertex
  fVtx = fAOD->GetPrimaryVertex();
  fVtx->GetXYZ(fVetex);
  AliAODVertex* vtSPD = fAOD->GetPrimaryVertexSPD();
  double vx = fVetex[0];
  double vy = fVetex[1];
  double vz = fVetex[2];
  double dz = vz - fAOD->GetPrimaryVertexSPD()->GetZ();
  if (fabs(vz)>(double)fZvtxCut) return;
  if (!fVtx || fVtx->GetNContributors() < 2 || vtSPD->GetNContributors()<1) return;
  hVz[0]->Fill(vz);
  // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/AliDPGtoolsEventProp
  // fEventCuts.SetCentralityEstimators("V0M","CL1");
  // if (!fEventCuts->AcceptEvent(fAOD) ) return;
  if (fPeriod.EqualTo("LHC10h")  || fPeriod.EqualTo("LHC11h") ) {if (fabs(dz)>0.5) return;}
  else if (fPeriod.EqualTo("LHC15o") ){
      double covTrc[6],covSPD[6];
      fVtx->GetCovarianceMatrix(covTrc);
      fAOD->GetPrimaryVertexSPD()->GetCovarianceMatrix(covSPD);
      double errTot = TMath::Sqrt(covTrc[5]+covSPD[5]);
      double errTrc = TMath::Sqrt(covTrc[5]);
      double nsigTot = TMath::Abs(dz)/errTot, nsigTrc = TMath::Abs(dz)/errTrc;
      if (fabs(dz)>0.2 || nsigTot>10 || nsigTrc>20) return;
  }
  hVz[1]->Fill(vz); 
  for (int i = 0; i < 20; ++i) {
      if (vz > -10+i*1 && vz < -10+(i+1)*1) {fVzBin = i; break;}
  }
  if (fVzBin<-990) return;
  hEvtCount->Fill(5);
  if (fDebug) Printf("vertex done!");

  // centrality
  double centV0M = -1, centTRK = -1, centSPD0 = -1, centSPD1 = -1, centV0A = -1;
  if (fPeriod.EqualTo("LHC10h") || fPeriod.EqualTo("LHC11h")){
    centV0M  = fAOD->GetCentrality()->GetCentralityPercentile("V0M");
    centTRK  = fAOD->GetCentrality()->GetCentralityPercentile("TRK");
    centSPD0 = fAOD->GetCentrality()->GetCentralityPercentile("CL0");
    centSPD1 = fAOD->GetCentrality()->GetCentralityPercentile("CL1");
    centV0A  = fAOD->GetCentrality()->GetCentralityPercentile("V0A");
  } else if (fPeriod.EqualTo("LHC15o") || fPeriod.EqualTo("LHC18q")) {
    AliMultSelection* fMultSel = (AliMultSelection*)InputEvent()->FindListObject("MultSelection");
    centV0M  = fMultSel->GetMultiplicityPercentile("V0M");
    centTRK  = fMultSel->GetMultiplicityPercentile("TRK");
    centSPD0 = fMultSel->GetMultiplicityPercentile("CL0");
    centSPD1 = fMultSel->GetMultiplicityPercentile("CL1");
  }
  fCent  = centV0M;
  hCentQA[0]->Fill(centV0M,centSPD1);
  hCentQA[2]->Fill(centV0M,centTRK);
  hCentQA[4]->Fill(centV0M,centSPD0);
  hCentQA[6]->Fill(centSPD1,centSPD0);
  if (fabs(fCent-centSPD1)>fCentDiffCut) return;
  hCentQA[1]->Fill(centV0M,centSPD1);
  hCentQA[3]->Fill(centV0M,centTRK);
  hCentQA[5]->Fill(centV0M,centSPD0);
  hCentQA[7]->Fill(centSPD1,centSPD0);
  if (fCent < 0 || fCent > 90) return;
  // cent bin
  fCentBin = (int)fCent/10;
  hCent[0]->Fill(fCent);
  hEvtCount->Fill(6);
  if (fDebug) Printf("centrality done!");

  // pile up
  if (fPeriod.EqualTo("LHC10h")) if(!RemovalForRun1()) return;
  if (fPeriod.EqualTo("LHC11h")) if(!RemovalForRun1()) return;
  if (fPeriod.EqualTo("LHC15o")) {
    // hMultCentQA[0]->Fill(fCent, fAOD->GetNumberOfTracks()); // raw Trk Multi Vs Cent(V0M)
    // if (PileUpMultiVertex(fAOD)) return;
    // if (!RejectEvtMultComp(fAOD)) return;
    // hMultCentQA[1]->Fill(fCent, fAOD->GetNumberOfTracks()); // Mult_Cent QA
    // if (!AODPileupCheck (fAOD)) return;
    if (!RejectEvtTFFit()) return; // 15o_pass2
  }
  if (fPeriod.EqualTo("LHC18q")) if (!RejectEvtTFFit()) return;
  hCent[1]->Fill(fCent);
  hEvtCount->Fill(7);
  if (fDebug) Printf("pile-up done!");

  if(!GetVZEROPlane()) return;
  hEvtCount->Fill(8);
  // analysis 
  if (!AnalyzeAOD()) return;
  hEvtCount->Fill(9);

  //TODO
  //1.  测试15o的数据
  //2.  添加18o的支持
  //3.  添加h-h关联

  
  //------------------
  // done
  //------------------
  if (fDebug) Printf("analysis done!");
  PostData(1,fOutputList);
}



//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::AnalyzeAOD()
{
  double SumQ2xTPCPos;
  double SumQ2yTPCPos;
  double fWgtMultTPCPos;

  double SumQ2xTPCNeg;
  double SumQ2yTPCNeg;
  double fWgtMultTPCNeg;

  std::vector<int>    vecPosEPTrkID;
  std::vector<int>    vecNegEPTrkID;
  std::vector<double> vecPosEPTrkPhi;
  std::vector<double> vecNegEPTrkPhi;
  std::vector<double> vecPosEPTrkNUAWgt;
  std::vector<double> vecNegEPTrkNUAWgt;

  std::vector<int>    vecPDGCode;
	std::vector<double> vecPhi;
	std::vector<double> vecEta;
	std::vector<double> vecPt;
	std::vector<int>    vecID;
	std::vector<double> vecNUAWeight;
	std::vector<double> vecNUEWeight;
	std::vector<double> vecNUAWeightPID;
	std::vector<double> vecNUEWeightPID;

  int nTrk = fAOD->GetNumberOfTracks();
  if (nTrk<4) return false;
  for (int iTrk = 0; iTrk < nTrk; ++iTrk) {
    AliAODTrack* track = (AliAODTrack*)fAOD->GetTrack(iTrk);
    if (!track) {
      AliError(Form("%s: Could not get Track", GetName()));
      continue;
    }
    if (!track->TestFilterBit(fFltbit)) continue; 
    if (!AcceptAODTrack(track)) continue;
    //------------------
    // NUE & NUA
    //------------------
    double phi = track->Phi();
    double  pt = track->Pt();
    double eta = track->Eta();
    int charge = track->Charge();
    int     id = track->GetID();

    hPhi[0]->Fill(phi);
    hEtaPhi[0]->Fill(phi,eta);
    double weight=1;
    if (fDoNUE) {
      double wEffi = GetNUECor(charge, pt);
      if (wEffi<0) continue;
      else weight *= wEffi;
    }
    if (fDoNUA){
      double wAcc = GetNUACor(charge, phi, eta, fVetex[2]);
      if (wAcc<0) continue;
      else weight *= wAcc;
      hPhi[1]->Fill(phi, wAcc);
      hEtaPhi[1]->Fill(phi,eta,wAcc);
    }
    
    if (pt > fPlanePtMin && pt < fPlanePtMax) {
      ///TODO Use Pt as weight for Better resolution ?
      if(eta >= fEtaGapPos) {
        SumQ2xTPCPos   += weight*TMath::Cos(2*phi);
        SumQ2yTPCPos   += weight*TMath::Sin(2*phi);      
        fWgtMultTPCPos += weight; 
        vecPosEPTrkID.push_back(id);
        vecPosEPTrkPhi.push_back(phi);
        vecPosEPTrkNUAWgt.push_back(weight);
      } else if(eta <= fEtaGapNeg) {
        SumQ2xTPCNeg   += weight*TMath::Cos(2*phi);
        SumQ2yTPCNeg   += weight*TMath::Sin(2*phi);      
        fWgtMultTPCNeg += weight;
        vecNegEPTrkID.push_back(id);
        vecNegEPTrkPhi.push_back(phi);
        vecNegEPTrkNUAWgt.push_back(weight);
      }
    }

    bool isItPiontrk = CheckPIDofParticle(track,1); // 1=pion
	  bool isItKaontrk = CheckPIDofParticle(track,2); // 2=Kaon
	  bool isItProttrk = CheckPIDofParticle(track,3); // 3=proton
	
    int code = 0;
	  if(charge > 0) {
      code = 999;
	    if(isItPiontrk)      code = 211;
	    else if(isItKaontrk) code = 321;
	    else if(isItProttrk) code = 2212;
	  } else{  /// 
      code = -999;
	    if(isItPiontrk)      code = -211;
	    else if(isItKaontrk) code = -321;
	    else if(isItProttrk) code = -2212;
	  }
	  
	  vecPDGCode.push_back(code);
	  vecPhi.push_back(phi);
	  vecEta.push_back(eta);
	  vecPt.push_back(pt);
	  vecID.push_back(id);
  }//loop track end
  hEvtCount->Fill(9);
  //Get TPC Plane
  fPsi2TPCNeg = GetEventPlane(SumQ2xTPCNeg,SumQ2xTPCNeg,2);
  fPsi2TPCPos = GetEventPlane(SumQ2xTPCPos,SumQ2xTPCPos,2);
  //resolution 
  hTPCPsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2TPCPos - 2*fPsi2TPCNeg));
  hV0CV0APsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2V0C - 2*fPsi2V0A));
  hV0CTPCPosPsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2V0C - 2*fPsi2TPCPos));
  hV0ATPCPosPsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2V0A - 2*fPsi2TPCPos));
  hV0CTPCNegPsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2V0C - 2*fPsi2TPCNeg));
  hV0ATPCNegPsi2Correlation -> Fill(fCent, TMath::Cos(2*fPsi2V0A - 2*fPsi2TPCNeg));
  hEvtCount->Fill(10);


  ///------------------------------------------
  ///   Lambda PID: 
  ///
  /// This part Below runs the loop over v0
  ///  and fills only lambda-xxx pairs:
  ///  
  ///------------------------------------------  
  std::vector<int>    vecLambdaCode;
  std::vector<double> vecLambdaPhi;
  std::vector<double> vecLambdaPt;
  std::vector<int>    vecDaughterPosID; // Pos Daughter ID
  std::vector<int>    vecDaughterNegID; // Neg Daughter ID
    
  Int_t nV0s = fAOD->GetNumberOfV0s();
  for (Int_t iV0 = 0; iV0 < nV0s; iV0++) {
    AliAODv0 *v0 = fAOD->GetV0(iV0);
    if (!v0) {
      AliError(Form("%s: Could not get v0s", GetName()));
      continue;
    }
    //Basic kinematic variable
    Double_t pt      = v0->Pt();
    Double_t eta     = v0->PseudoRapV0();
    Double_t dcaToPV = v0->DcaV0ToPrimVertex();//DCA to Primary Vertex
    Double_t CPA     = v0->CosPointingAngle(fVetex);//cosine pointing angle
    Double_t dl      = v0->DecayLengthV0(fVetex);
    fHistV0Pt              -> Fill(pt);
    fHistV0Eta             -> Fill(eta);
    fHistV0DcatoPrimVertex -> Fill(dcaToPV);
    fHistV0CPA             -> Fill(CPA);
    fHistV0DecayLength     -> Fill(dl);
    //V0 cut
    if(!IsGoodV0(v0)) continue;
    //V0 daughters cut
    AliAODTrack *nTrack = dynamic_cast<AliAODTrack *>(v0->GetDaughter(1));
    AliAODTrack *pTrack = dynamic_cast<AliAODTrack *>(v0->GetDaughter(0));
    if(!(IsGoodDaughterTrack(nTrack)) || !(IsGoodDaughterTrack(pTrack))) continue;
    Float_t nDcaPV = v0->DcaNegToPrimVertex();
    Float_t pDcaPV = v0->DcaPosToPrimVertex();
    if( nDcaPV<fDaughtersDCAToPrimVtxMin || pDcaPV<fDaughtersDCAToPrimVtxMin) continue;
    Int_t code = GetLambdaCode(pTrack,nTrack);
    if(TMath::Abs(code) != 3122) continue;
    TVector2 Vt(v0->MomV0X(), v0->MomV0Y());
    Double_t phi = Vt.Phi() > 0 ? Vt.Phi() : Vt.Phi() + TMath::TwoPi();
    Int_t id_posDaughter = v0->GetPosID();
    Int_t id_negDaughter = v0->GetNegID();

    if (code == 3122) {
      Double_t massLambda  = v0->MassLambda();
      fHistLambdaPt[0]              -> Fill(pt);
      fHistLambdaEta[0]             -> Fill(eta);
      fHistLambdaPhi[0]             -> Fill(phi);
      fHistLambdaDcaToPrimVertex[0] -> Fill(dcaToPV);
      fHistLambdaCPA[0]             -> Fill(CPA);
      fHistLambdaDecayLength[0]     -> Fill(dl);
      fHistLambdaMass[0]            -> Fill(massLambda);
      fProfileLambdaMassVsPt[0]     -> Fill(pt, massLambda);
      if (TMath::Abs(massLambda - fMassMean) < fLambdaMassCut) {
        //if a particle has been used as daughter particle before(It happends), we have to refuse a new one.
        if (find(vecDaughterPosID.begin(), vecDaughterPosID.end(), id_posDaughter) != vecDaughterPosID.end()) continue;
        if (find(vecDaughterNegID.begin(), vecDaughterNegID.end(), id_negDaughter) != vecDaughterNegID.end()) continue;
        fHistLambdaPt[1]              -> Fill(pt);
        fHistLambdaEta[1]             -> Fill(eta);
        fHistLambdaPhi[1]             -> Fill(phi);
        fHistLambdaDcaToPrimVertex[1] -> Fill(dcaToPV);
        fHistLambdaCPA[1]             -> Fill(CPA);
        fHistLambdaDecayLength[1]     -> Fill(dl);
        fHistLambdaMass[1]            -> Fill(massLambda);
        fProfileLambdaMassVsPt[1]     -> Fill(pt, massLambda);
        vecLambdaCode.push_back(code);
        vecLambdaPhi.push_back(phi);
        vecLambdaPt.push_back(pt);
        vecDaughterPosID.push_back(id_posDaughter);
        vecDaughterNegID.push_back(id_negDaughter);
      }
    } 

    if (code == -3122) {
      Double_t massAntiLambda  = v0->MassAntiLambda();
      fHistAntiLambdaPt[0]              -> Fill(pt);
      fHistAntiLambdaEta[0]             -> Fill(eta);
      fHistAntiLambdaPhi[0]             -> Fill(phi);
      fHistAntiLambdaDcaToPrimVertex[0] -> Fill(dcaToPV);
      fHistAntiLambdaCPA[0]             -> Fill(CPA);
      fHistAntiLambdaDecayLength[0]     -> Fill(dl);
      fHistAntiLambdaMass[0]            -> Fill(massAntiLambda);
      fProfileAntiLambdaMassVsPt[0]     -> Fill(pt, massAntiLambda);

      if (TMath::Abs(massAntiLambda - fMassMean) < fLambdaMassCut) {
        if (find(vecDaughterPosID.begin(), vecDaughterPosID.end(), id_posDaughter) != vecDaughterPosID.end()) continue;
        if (find(vecDaughterNegID.begin(), vecDaughterNegID.end(), id_negDaughter) != vecDaughterNegID.end()) continue;
        fHistAntiLambdaPt[1]              -> Fill(pt);
        fHistAntiLambdaEta[1]             -> Fill(eta);
        fHistAntiLambdaPhi[1]             -> Fill(phi);
        fHistAntiLambdaDcaToPrimVertex[1] -> Fill(dcaToPV);
        fHistAntiLambdaCPA[1]             -> Fill(CPA);
        fHistAntiLambdaDecayLength[1]     -> Fill(dl);
        fHistAntiLambdaMass[1]            -> Fill(massAntiLambda);
        fProfileAntiLambdaMassVsPt[1]     -> Fill(pt, massAntiLambda);
          
        vecLambdaCode.push_back(code);
        vecLambdaPhi.push_back(phi);
        vecLambdaPt.push_back(pt);
        vecDaughterPosID.push_back(id_posDaughter);
        vecDaughterNegID.push_back(id_negDaughter);
      }
    } 
  }//loop V0 end
  hEvtCount->Fill(11);


  ///------------------------------------------
  ///   Fill Lambda-X correlations:
  ///
  /// This part Below runs the loop over v0
  ///  and fills only lambda-xxx pairs:
  ///  
  ///------------------------------------------  

  //Lambda - X
  for (std::vector<Double_t>::size_type jLambda = 0; jLambda < vecLambdaPhi.size(); jLambda++) {
    Int_t    code_lambda    = vecLambdaCode[jLambda];
    Double_t phi_lambda     = vecLambdaPhi[jLambda];
    Double_t pt_lambda      = vecLambdaPt[jLambda];
    Int_t    id_posDaughter = vecDaughterPosID[jLambda];
    Int_t    id_negDaughter = vecDaughterNegID[jLambda];
    //Remove AutoCorrelation:
    Double_t fPosTPCQxTemp = 0., fPosTPCQyTemp = 0.; ///Get the Total sum of Pos TPC Qx,Qy  locally, then Remove AutoCorr if needed.
    Double_t fNegTPCQxTemp = 0., fNegTPCQyTemp = 0.; ///Get the Total sum of Neg TPC Qx,Qy  locally, then Remove AutoCorr if needed.
    Double_t fPosTPCMult   = 0., fNegTPCMult   = 0.;
    Double_t qxPosTPC = 0., qyPosTPC = 0.;
    Double_t qxNegTPC = 0., qyNegTPC = 0.;
    // use EP from opposite eta than the charged track! One way to remove AutoCorrelation.
    fNegTPCQxTemp = SumQ2xTPCNeg;
    fNegTPCQyTemp = SumQ2yTPCNeg;
    fNegTPCMult   = fWgtMultTPCNeg;

    fPosTPCQxTemp = SumQ2xTPCPos;
    fPosTPCQyTemp = SumQ2yTPCPos;
    fPosTPCMult   = fWgtMultTPCPos;
      
    //for NegEP
    std::vector<Int_t>::iterator iterPosDaughterNegTPC = find(vecNegEPTrkID.begin(), vecNegEPTrkID.end(), id_posDaughter);
    std::vector<Int_t>::iterator iterNegDaughterNegTPC = find(vecNegEPTrkID.begin(), vecNegEPTrkID.end(), id_negDaughter);
      
    //for PosEP
    std::vector<Int_t>::iterator iterPosDaughterPosTPC = find(vecPosEPTrkID.begin(), vecPosEPTrkID.end(), id_posDaughter);
    std::vector<Int_t>::iterator iterNegDaughterPosTPC = find(vecPosEPTrkID.begin(), vecPosEPTrkID.end(), id_negDaughter);
	
    if (iterPosDaughterNegTPC != vecNegEPTrkID.end()) {
      Int_t iDaughter = distance(vecNegEPTrkID.begin(), iterPosDaughterNegTPC);
      qxNegTPC +=  vecNegEPTrkNUAWgt[iDaughter] * TMath::Cos(2 * vecNegEPTrkPhi[iDaughter]);
      qyNegTPC +=  vecNegEPTrkNUAWgt[iDaughter] * TMath::Sin(2 * vecNegEPTrkPhi[iDaughter]);
      fNegTPCMult -= vecNegEPTrkNUAWgt[iDaughter];
    }

    if (iterNegDaughterNegTPC != vecNegEPTrkID.end()) {
      Int_t iDaughter = distance(vecNegEPTrkID.begin(), iterNegDaughterNegTPC);
      qxNegTPC += vecNegEPTrkNUAWgt[iDaughter] * TMath::Cos(2 * vecNegEPTrkPhi[iDaughter]);
      qyNegTPC += vecNegEPTrkNUAWgt[iDaughter] * TMath::Sin(2 * vecNegEPTrkPhi[iDaughter]);
      fNegTPCMult -= vecNegEPTrkNUAWgt[iDaughter];
    }

    if (iterPosDaughterPosTPC != vecPosEPTrkID.end()) {
      Int_t iDaughter = distance(vecPosEPTrkID.begin(), iterPosDaughterPosTPC);
      qxPosTPC += vecPosEPTrkNUAWgt[iDaughter] * TMath::Cos(2 * vecPosEPTrkPhi[iDaughter]);
      qyPosTPC += vecPosEPTrkNUAWgt[iDaughter] * TMath::Sin(2 * vecPosEPTrkPhi[iDaughter]);
      fPosTPCMult -= vecPosEPTrkNUAWgt[iDaughter];
    }
    
    if (iterNegDaughterPosTPC != vecPosEPTrkID.end()) {
      Int_t iDaughter = distance(vecPosEPTrkID.begin(), iterNegDaughterPosTPC);
      qxPosTPC +=  vecPosEPTrkNUAWgt[iDaughter] * TMath::Cos(2 * vecPosEPTrkPhi[iDaughter]);
      qyPosTPC +=  vecPosEPTrkNUAWgt[iDaughter] * TMath::Sin(2 * vecPosEPTrkPhi[iDaughter]);
      fPosTPCMult -= vecPosEPTrkNUAWgt[iDaughter];
    }

    fPosTPCQxTemp -= qxPosTPC;   /// qx=0,qy=0 if Lambda daughters are on the opposite eta of the EP used.. 
    fPosTPCQyTemp -= qyPosTPC;

    fNegTPCQxTemp -= qxNegTPC;   /// qx=0,qy=0 if Lambda daughters are on the opposite eta of the EP used.. 
    fNegTPCQyTemp -= qyNegTPC;
    
    if(fPosTPCMult > 0. && fNegTPCMult > 0.) {
      fPosTPCQxTemp = fPosTPCQxTemp/fPosTPCMult;
      fPosTPCQyTemp = fPosTPCQyTemp/fPosTPCMult;
      fNegTPCQxTemp = fNegTPCQxTemp/fNegTPCMult;
      fNegTPCQyTemp = fNegTPCQyTemp/fNegTPCMult;
    } else continue;

    Double_t fPsi2PosTPCNoAuto = GetEventPlane(fPosTPCQyTemp,fPosTPCQxTemp,2.);   //AutoCorrelation Removed Pos EP.
    Double_t fPsi2NegTPCNoAuto = GetEventPlane(fNegTPCQyTemp,fNegTPCQxTemp,2.);   //AutoCorrelation Removed Neg EP.

    //Check the PID Flow
    if(fIsCheckPIDFlow) {
      double phi_lambda_tmp = phi_lambda;
      if(phi_lambda < TMath::Pi()) phi_lambda_tmp += TMath::Pi();
      Double_t dPhiTPCPos = phi_lambda_tmp - fPsi2PosTPCNoAuto;
      Double_t dPhiTPCNeg = phi_lambda_tmp - fPsi2NegTPCNoAuto;
      Double_t dPhiV0C = phi_lambda_tmp - fPsi2V0C;
      Double_t dPhiV0A = phi_lambda_tmp - fPsi2V0A; 

      if(dPhiTPCPos < 0) dPhiTPCPos += TMath::Pi();
      if(dPhiTPCNeg < 0) dPhiTPCNeg += TMath::Pi();
      if(dPhiV0C    < 0) dPhiV0C    += TMath::Pi();
      if(dPhiV0A    < 0) dPhiV0A    += TMath::Pi();

      if(dPhiTPCPos > TMath::Pi()) dPhiTPCPos -= TMath::Pi();
      if(dPhiTPCNeg > TMath::Pi()) dPhiTPCNeg -= TMath::Pi();
      if(dPhiV0C    > TMath::Pi()) dPhiV0C    -= TMath::Pi();
      if(dPhiV0A    > TMath::Pi()) dPhiV0A    -= TMath::Pi();
        
      if(code_lambda == 3122) {
        fHist3DdNdPhiCentPtLambda[0]->Fill(fCent, pt_lambda, dPhiTPCPos);
        fHist3DdNdPhiCentPtLambda[1]->Fill(fCent, pt_lambda, dPhiTPCNeg);
        fHist3DdNdPhiCentPtLambda[2]->Fill(fCent, pt_lambda, dPhiV0C);
        fHist3DdNdPhiCentPtLambda[3]->Fill(fCent, pt_lambda, dPhiV0A);
      }

      if(code_lambda == -3122) {
        fHist3DdNdPhiCentPtAntiLambda[0]->Fill(fCent, pt_lambda, dPhiTPCPos);
        fHist3DdNdPhiCentPtAntiLambda[1]->Fill(fCent, pt_lambda, dPhiTPCNeg);
        fHist3DdNdPhiCentPtAntiLambda[2]->Fill(fCent, pt_lambda, dPhiV0C);
        fHist3DdNdPhiCentPtAntiLambda[3]->Fill(fCent, pt_lambda, dPhiV0A);
      }
    }

    for (std::vector<Double_t>::size_type iTrk = 0; iTrk < vecPhi.size(); iTrk++) {
      Int_t    id   = vecID[iTrk];
      Int_t    code = vecPDGCode[iTrk];
      Double_t pt   = vecPt[iTrk];
      Double_t eta  = vecEta[iTrk];
      Double_t phi  = vecPhi[iTrk];
      if(id == id_posDaughter || id == id_negDaughter) continue;

      Double_t fPsiNTPCNoAuto = -999;
      if (eta > 0.) fPsiNTPCNoAuto = fPsi2NegTPCNoAuto;
      else fPsiNTPCNoAuto = fPsi2PosTPCNoAuto;
  
      Double_t delta     = TMath::Cos(phi_lambda - phi);
      Double_t gammaTPC  = TMath::Cos(phi_lambda + phi - 2 *fPsiNTPCNoAuto);
      Double_t gammaV0C  = TMath::Cos(phi_lambda + phi - 2 *fPsi2V0C);
      Double_t gammaV0A  = TMath::Cos(phi_lambda + phi - 2 *fPsi2V0A);

      if (code > 0 && code_lambda ==  3122) {
        fProfileDelta_Lambda_hPos        -> Fill(fCent, delta);
        fProfileGammaTPC_Lambda_hPos     -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_Lambda_hPos     -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_Lambda_hPos     -> Fill(fCent, gammaV0A);
      }
      if (code < 0 && code_lambda ==  3122) {
        fProfileDelta_Lambda_hNeg        -> Fill(fCent, delta);
        fProfileGammaTPC_Lambda_hNeg     -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_Lambda_hNeg     -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_Lambda_hNeg     -> Fill(fCent, gammaV0A);
      } 
      if (code > 0 && code_lambda == -3122) {
        fProfileDelta_AntiLambda_hPos    -> Fill(fCent, delta);
        fProfileGammaTPC_AntiLambda_hPos -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_AntiLambda_hPos -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_AntiLambda_hPos -> Fill(fCent, gammaV0A);
      }
      if (code < 0 && code_lambda == -3122) {
        fProfileDelta_AntiLambda_hNeg    -> Fill(fCent, delta);
        fProfileGammaTPC_AntiLambda_hNeg -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_AntiLambda_hNeg -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_AntiLambda_hNeg -> Fill(fCent, gammaV0A);
      }
      if (code ==  2212 && code_lambda ==  3122) {
        fProfileDelta_Lambda_Proton      -> Fill(fCent, delta);
        fProfileGammaTPC_Lambda_Proton   -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_Lambda_Proton   -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_Lambda_Proton   -> Fill(fCent, gammaV0A);
      }
      if (code == -2212 && code_lambda ==  3122) {
        fProfileDelta_Lambda_AntiProton    -> Fill(fCent, delta);
        fProfileGammaTPC_Lambda_AntiProton -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_Lambda_AntiProton -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_Lambda_AntiProton -> Fill(fCent, gammaV0A);
      }
      if (code ==  2212 && code_lambda == -3122) {
        fProfileDelta_AntiLambda_Proton    -> Fill(fCent, delta);
        fProfileGammaTPC_AntiLambda_Proton -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_AntiLambda_Proton -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_AntiLambda_Proton -> Fill(fCent, gammaV0A);
      }
      if (code == -2212 && code_lambda == -3122) {
        fProfileDelta_AntiLambda_AntiProton    -> Fill(fCent, delta);
        fProfileGammaTPC_AntiLambda_AntiProton -> Fill(fCent, gammaTPC);
        fProfileGammaV0C_AntiLambda_AntiProton -> Fill(fCent, gammaV0C);
        fProfileGammaV0A_AntiLambda_AntiProton -> Fill(fCent, gammaV0A);
      }
    }// (Anti)Lambda-X pair done 
  }/// loop over charge particle array

  if(fIsCheckPIDFlow) {
    for (std::vector<Double_t>::size_type iTrk = 0; iTrk < vecPhi.size(); iTrk++) {
      Int_t    code = vecPDGCode[iTrk];
      Double_t pt   = vecPt[iTrk];
      Double_t eta  = vecEta[iTrk];
      Double_t phi  = vecPhi[iTrk];

      Double_t dPhiTPCPos = phi - fPsi2TPCPos;
      Double_t dPhiTPCNeg = phi - fPsi2TPCNeg;
      Double_t dPhiV0C    = phi - fPsi2V0C;
      Double_t dPhiV0A    = phi - fPsi2V0A;

      if(dPhiTPCPos < 0) dPhiTPCPos += TMath::Pi();
      if(dPhiTPCNeg < 0) dPhiTPCNeg += TMath::Pi();
      if(dPhiV0C    < 0) dPhiV0C    += TMath::Pi();
      if(dPhiV0A    < 0) dPhiV0A    += TMath::Pi();

      if(dPhiTPCPos > TMath::Pi()) dPhiTPCPos -= TMath::Pi();
      if(dPhiTPCNeg > TMath::Pi()) dPhiTPCNeg -= TMath::Pi();
      if(dPhiV0C    > TMath::Pi()) dPhiV0C    -= TMath::Pi();
      if(dPhiV0A    > TMath::Pi()) dPhiV0A    -= TMath::Pi();
        
      if (code > 0) {
        if (eta > 0) fHist3DdNdPhiCentPthPos[0]->Fill(fCent, pt, dPhiTPCNeg);
        else         fHist3DdNdPhiCentPthPos[0]->Fill(fCent, pt, dPhiTPCPos);
        fHist3DdNdPhiCentPthPos[1]->Fill(fCent, pt, dPhiV0C);
        fHist3DdNdPhiCentPthPos[2]->Fill(fCent, pt, dPhiV0A);
      }
      if (code < 0) {
        if (eta > 0) fHist3DdNdPhiCentPthNeg[0]->Fill(fCent, pt, dPhiTPCNeg);
        else         fHist3DdNdPhiCentPthNeg[0]->Fill(fCent, pt, dPhiTPCPos);
        fHist3DdNdPhiCentPthNeg[1]->Fill(fCent, pt, dPhiV0C);
        fHist3DdNdPhiCentPthNeg[2]->Fill(fCent, pt, dPhiV0A);
      }
      if (code == 2212) {
        if (eta > 0) fHist3DdNdPhiCentPtProton[0]->Fill(fCent, pt, dPhiTPCNeg);
        else         fHist3DdNdPhiCentPtProton[0]->Fill(fCent, pt, dPhiTPCPos);
        fHist3DdNdPhiCentPtProton[1]->Fill(fCent, pt, dPhiV0C);
        fHist3DdNdPhiCentPtProton[2]->Fill(fCent, pt, dPhiV0A);
      }
      if (code == -2212) {
        if (eta > 0) fHist3DdNdPhiCentPtAntiProton[0]->Fill(fCent, pt, dPhiTPCNeg);
        else         fHist3DdNdPhiCentPtAntiProton[0]->Fill(fCent, pt, dPhiTPCPos);
        fHist3DdNdPhiCentPtAntiProton[1]->Fill(fCent, pt, dPhiV0C);
        fHist3DdNdPhiCentPtAntiProton[2]->Fill(fCent, pt, dPhiV0A);
      }
    }
  }////--------- PID Flow hist are Filled ----------
  hEvtCount->Fill(12);
  return true;
}

//---------------------------------------------------

double AliAnalysisTaskLambdaProtonCVE::GetNUECor(int charge, double pt)
{
  double weightNUE = 1;
  if (fPeriod.EqualTo("LHC10h")){
    // hNUEweightPlus = (TH1D*)fListNUE->FindObject("effVsPtPlus");
    // hNUEweightMinus = (TH1D*)fListNUE->FindObject("effVsfPtMinus");
    if (charge>0){
      hNUEweightPlus = (TH1D*)fListNUE->FindObject(Form("effVsPt_cent%iPlus",fCentBin));
      if (!hNUEweightPlus) return -1;
      int ptBin = hNUEweightPlus->GetXaxis()->FindBin(pt);
      if (hNUEweightPlus->GetBinContent(ptBin)>0){
        weightNUE = 1./ hNUEweightPlus->GetBinContent(ptBin); 
      } 
      else return -1;
    }
    if (charge<0){
      hNUEweightMinus = (TH1D*)fListNUE->FindObject(Form("effVsPt_cent%iMinus",fCentBin));
      if (!hNUEweightMinus) return -1;
      int ptBin = hNUEweightMinus->GetXaxis()->FindBin(pt);
      if (hNUEweightMinus->GetBinContent(ptBin)>0){
        weightNUE = 1./ hNUEweightMinus->GetBinContent(ptBin); 
      }  
      else return -1;  
    }
  } 
  else if (fPeriod.EqualTo("LHC15o")){
    if (charge>0){
      hNUEweightPlus = (TH1D*)fListNUE->FindObject("trkEfficiencyChrgPos");
      if (!hNUEweightPlus) return -1;
      int ptBin = hNUEweightPlus->GetXaxis()->FindBin(pt);
      if (hNUEweightPlus->GetBinContent(ptBin)>0){
        weightNUE = 1./ hNUEweightPlus->GetBinContent(ptBin); 
      } 
      else return -1;
    }
    if (charge<0){
      hNUEweightMinus = (TH1D*)fListNUE->FindObject("trkEfficiencyChrgNeg");
      if (!hNUEweightMinus) return -1;
      int ptBin = hNUEweightMinus->GetXaxis()->FindBin(pt);
      if (hNUEweightMinus->GetBinContent(ptBin)>0){
        weightNUE = 1./ hNUEweightMinus->GetBinContent(ptBin); 
      } 
      else return -1;
    }
  }
  return weightNUE;
}

//---------------------------------------------------

double AliAnalysisTaskLambdaProtonCVE::GetNUACor(int charge, double phi, double eta, double vz)
{
  double weightNUA = 1;
  if (fVzBin<0 || fCentBin<0 || fRunNum<0) return -1;
  if (fPeriod.EqualTo("LHC10h")){
    hNUAweightPlus = (TH2D*)fListNUA->FindObject(Form("weightdPhidEta_run%i_cent0_vz%i_plus",fRunNum, fVzBin));
    hNUAweightMinus = (TH2D*)fListNUA->FindObject(Form("weightdPhidEta_run%i_cent0_vz%i_minus",fRunNum, fVzBin));
    if(!hNUAweightPlus || !hNUAweightMinus) return -1;
    if (charge>0){ 
      int phiBin = hNUAweightPlus->GetXaxis()->FindBin(phi);
      int etaBin = hNUAweightPlus->GetYaxis()->FindBin(eta);  
      if (hNUAweightPlus->GetBinContent(phiBin, etaBin)>0) weightNUA = hNUAweightPlus->GetBinContent(phiBin, etaBin);
      return weightNUA;
    } else if (charge<0){
      int phiBin = hNUAweightMinus->GetXaxis()->FindBin(phi);
      int etaBin = hNUAweightMinus->GetYaxis()->FindBin(eta);  
      if (hNUAweightMinus->GetBinContent(phiBin, etaBin)>0) weightNUA = hNUAweightMinus->GetBinContent(phiBin, etaBin);
      return weightNUA;
    } 
  } else if (fPeriod.EqualTo("LHC15o")){ // Rihan and Protty 's NUA Results
    if (charge>0){ 
      hCorrectNUAPos = (TH3F*) fListNUA->FindObject(Form("fHist_NUA_VzPhiEta_Charge_Pos_Cent0_Run%d",fRunNum));
      if (!hCorrectNUAPos) return -1;
      int iBinNUA = hCorrectNUAPos->FindBin(vz,phi,eta); 
      if (hCorrectNUAPos->GetBinContent(iBinNUA)>0) weightNUA = (double)hCorrectNUAPos->GetBinContent(iBinNUA);
      return  weightNUA;
    } else if (charge<0){
      hCorrectNUANeg = (TH3F*) fListNUA->FindObject(Form("fHist_NUA_VzPhiEta_Charge_Neg_Cent0_Run%d",fRunNum));
      if (!hCorrectNUANeg) return -1;
      int iBinNUA = hCorrectNUANeg->FindBin(vz,phi,eta); 
      if (hCorrectNUANeg->GetBinContent(iBinNUA)>0) weightNUA = (double)hCorrectNUANeg->GetBinContent(iBinNUA);
      return weightNUA;
    } 
    // In Rihan and Protty 's NUA results, the phi distribution is independent on centrality and particle charge
  }
  return weightNUA;
}

//---------------------------------------------------

int AliAnalysisTaskLambdaProtonCVE::GetRunNumBin(int runNum)
{
  int runNBin=-1;
  if (fPeriod.EqualTo("LHC10h") ){
      int runNumList[90]={
        139510, 139507, 139505, 139503, 139465, 139438, 139437, 139360, 139329, 139328, 139314, 139310,
        139309, 139173, 139107, 139105, 139038, 139037, 139036, 139029, 139028, 138872, 138871, 138870,
        138837, 138732, 138730, 138666, 138662, 138653, 138652, 138638, 138624, 138621, 138583, 138582,
        138579, 138578, 138534, 138469, 138442, 138439, 138438, 138396, 138364, 138275, 138225, 138201,
        138197, 138192, 138190, 137848, 137844, 137752, 137751, 137724, 137722, 137718, 137704, 137693,
        137692, 137691, 137686, 137685, 137639, 137638, 137608, 137595, 137549, 137546, 137544, 137541,
        137539, 137531, 137530, 137443, 137441, 137440, 137439, 137434, 137432, 137431, 137430, 137243,
        137236, 137235, 137232, 137231, 137162, 137161};
      for (int i = 0; i < 90; ++i) {
        if (runNum==runNumList[i]) {runNBin=i; break;}
        else continue;
      }
  } else if (fPeriod.EqualTo("LHC11h") ){
      int runNumList[39]={
        170387,170040,170268,170228,170207,169838,170159,170204,170311,170084,
        169835,170088,170593,170203,170270,169846,170163,170388,170155,170083,
        170572,169837,169855,170306,170269,170089,170309,170091,170081,170230,
        170085,170315,170027,170193,170312,170313,170308,169858,169859};
        for (int i = 0; i < 39; ++i) {
          if (runNum==runNumList[i]) {runNBin=i; break;}
          else continue;
        }
  } else if (fPeriod.EqualTo("LHC15o") ){
      int runNumList[138]={
        246994, 246991, 246989, 246984, 246982, 246948, 246945, 246928, 246871, 246870, 246867, 246865, 
        246864, 246859, 246858, 246851, 246847, 246846, 246845, 246844, 246810, 246809, 246808, 246807, 
        246805, 246804, 246766, 246765, 246763, 246760, 246759, 246758, 246757, 246751, 246750, 246434, 
        246431, 246424, 246392, 246391, 246276, 246275, 246272, 246271, 246225, 246222, 246217, 246185, 
        246182, 246181, 246180, 246178, 246153, 246152, 246151, 246148, 246115, 246113, 246089, 246087, 
        246053, 246052, 246049, 246048, 246042, 246037, 246036, 246012, 246003, 246001, 245963, 245954, 
        245952, 245949, 245923, 245833, 245831, 245829, 245793, 245785, 245775, 245766, 245759, 245752, 
        245731, 245729, 245705, 245702, 245692, 245683, 245554, 245545, 245544, 245543, 245542, 245540, 
        245535, 245507, 245505, 245504, 245501, 245497, 245496, 245454, 245453, 245450, 245446, 245441, 
        245411, 245410, 245409, 245407, 245401, 245397, 245396, 245353, 245349, 245347, 245346, 245345, 
        245343, 245259, 245233, 245232, 245231, 245152, 245151, 245146, 245145, 245068, 245066, 245064, 
        244983, 244982, 244980, 244975, 244918, 244917};
      for (int i = 0; i < 138; ++i) {
        if (runNum==runNumList[i]) {runNBin=i; break;}
        else continue;
      }
  }
  return runNBin;
}

//---------------------------------------------------

double AliAnalysisTaskLambdaProtonCVE::GetEventPlane(double qx, double qy, double harmonic) 
{
  double psi = (1./harmonic)*TMath::ATan2(qy,qx);
  if (psi < 0) return psi += TMath::TwoPi()/harmonic;
  else return psi;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RemovalForRun1()
{
  // pileup
  fUtils->SetUseOutOfBunchPileUp(true);
  fUtils->SetUseMVPlpSelection(true);
  // fUtils->SetMinPlpContribMV(5);
  bool isPileup = fUtils->IsPileUpEvent(fAOD);
  // bool isPileup = fUtils->IsPileUpMV(fAOD); // pp, p-Pb
  if (isPileup) return false;
  return true;   
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RejectEvtMultComp() // 15o_pass1, old pile-up
{
   // TPC cluster cut
    Int_t multEsd = ((AliAODHeader*)fAOD->GetHeader())->GetNumberOfESDTracks(); // multESD
    const Int_t nTrk = fAOD->GetNumberOfTracks();
    Int_t multTPC=0; // FB128 + Common Track Cuts
    Int_t multTPCFE=0; // FB1 + Common Track Cuts + chi2 > 0.2
    Int_t multGlobal=0; // FB16 + Common Track Cuts + Dca Cuts
    for (Int_t it1 = 0; it1 < nTrk; it1++) {
      AliAODTrack* aodTrk = (AliAODTrack*)fAOD->GetTrack(it1);
      if (!aodTrk) continue;
      if (aodTrk->TestFilterBit(128)) multTPC++;
      double Eta  = aodTrk->Eta();
      double Pt    = aodTrk->Pt();
      double Phi  = aodTrk->Phi();
      double charge = aodTrk->Charge();
      if(Pt<0.2 || Pt>5.0 || TMath::Abs(Eta)>0.8 || aodTrk->GetTPCNcls()<fNclsCut || aodTrk->GetTPCsignal()<10.0) continue;
      if(aodTrk->TestFilterBit(1) && aodTrk->Chi2perNDF()>0.2)  multTPCFE++;
      if(!aodTrk->TestFilterBit(16) || aodTrk->Chi2perNDF()<0.1)   continue;
      Double_t dca[2] = {-99., -99.};
      Double_t cov[3] = {-99., -99., -99.};
      Double_t magField = fAOD->GetMagneticField();
      if(magField!=0){     
        if(aodTrk->PropagateToDCA(fAOD->GetPrimaryVertex(), magField, 100., dca, cov) && TMath::Abs(dca[0]) < 0.3 && TMath::Abs(dca[1]) < 0.3) multGlobal++;    
      }
    }

    hMultMultQA[0]->Fill(multTPC,multEsd );
    hMultMultQA[1]->Fill(multGlobal,multTPCFE );

    //TODO
    TString fMultComp = "pileupByGlobalTPC1";

    if(fMultComp.EqualTo("pileupByEDSTPC128") ){ // Rihan
      if ((Double_t)(multEsd*(1/3.45) - 90.) < (Double_t)multTPC) 
      {
        hMultMultQA[3]->Fill(multTPC,multEsd);
        return true;
      }
      else return false;
    }

    if(fMultComp.EqualTo("pileupByGlobalTPC1") ) { // A.Dobrin
      if (multTPCFE-1.78*multGlobal<62.87 && multTPCFE-1.48*multGlobal>-36.73){
        hMultMultQA[4]->Fill(multGlobal,multTPCFE);
        return true;  
      } 
      else return false;
    } 

    return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RejectEvtTFFit()
{
  Float_t centV0M = -999;
  Float_t centCL1 = -999;
  Float_t centCL0 = -999;

  AliMultSelection* fMultSelection = (AliMultSelection*) InputEvent()->FindListObject("MultSelection");
  if(!fMultSelection) {
    printf("\n\n **WARNING** ::UserExec() AliMultSelection object not found.\n\n");
    exit(1);
  }
  centV0M = (Float_t) fCent;
  centCL1 = fMultSelection->GetMultiplicityPercentile("CL1");
  centCL0 = fMultSelection->GetMultiplicityPercentile("CL0");

  Int_t nITSClsLy0 = fAOD->GetNumberOfITSClusters(0);
  Int_t nITSClsLy1 = fAOD->GetNumberOfITSClusters(1);
  Int_t nITSCls = nITSClsLy0 + nITSClsLy1;

  AliAODTracklets* aodTrkl = (AliAODTracklets*)fAOD->GetTracklets();
  Int_t nITSTrkls = aodTrkl->GetNumberOfTracklets();
    
  const Int_t nTracks = fAOD->GetNumberOfTracks();
  Int_t multTrk = 0;
  for (Int_t it = 0; it < nTracks; it++) {
      AliAODTrack* aodTrk = (AliAODTrack*)fAOD->GetTrack(it);
      if (!aodTrk){
          delete aodTrk;
          continue;
      }
        
      if (aodTrk->TestFilterBit(32)){
        if ((TMath::Abs(aodTrk->Eta()) < 0.8) && (aodTrk->GetTPCNcls() >= 70) && (aodTrk->Pt() >= 0.2))
        multTrk++;
      }
  }

  hMultCentQA[0]->Fill(centV0M, multTrk); //  Mult(FB32) Vs Cent(V0M)

  AliAODVZERO* aodV0 = fAOD->GetVZEROData();
  Float_t multV0a = aodV0->GetMTotV0A();
  Float_t multV0c = aodV0->GetMTotV0C();
  Float_t multV0Tot = multV0a + multV0c;
  UShort_t multV0aOn = aodV0->GetTriggerChargeA();
  UShort_t multV0cOn = aodV0->GetTriggerChargeC();
  UShort_t multV0On = multV0aOn + multV0cOn;

  // pile-up cuts
  if (centCL0 < fCenCutLowPU->Eval(centV0M)) return false;        
  if (centCL0 > fCenCutHighPU->Eval(centV0M)) return false;
           
  if (Float_t(nITSCls) > fSPDCutPU->Eval(nITSTrkls)) return false;
           
  if (multV0On < fV0CutPU->Eval(multV0Tot)) return false;

  if (Float_t(multTrk) < fMultCutPU->Eval(centV0M)) return false;

  if (((AliAODHeader*)fAOD->GetHeader())->GetRefMultiplicityComb08() < 0) return false;

  if (fAOD->IsIncompleteDAQ()) return false;

  hMultCentQA[1]->Fill(centV0M, multTrk); //  Mult(FB32) Vs Cent(V0M)
  return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RejectEvtTPCITSfb32TOF ()
{
    //TOD+FB32 pile-up removal
    // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/AliDPGtoolsEventProp
    Int_t multTrk=0;
    Int_t multTrkTOF=0;
    int nTrk = fAOD->GetNumberOfTracks();
    for (Int_t it2 = 0; it2 < nTrk; it2++) {
      AliAODTrack* aodTrk = (AliAODTrack*)fAOD->GetTrack(it2);
      if (!aodTrk) continue;
      if (aodTrk->TestFilterBit(32)){
        multTrk++;
        if ( TMath::Abs(aodTrk->GetTOFsignalDz()) <= 10 && aodTrk->GetTOFsignal() >= 12000 && aodTrk->GetTOFsignal() <= 25000) multTrkTOF++;
        else return false; 
      }
    }
    hMultMultQA[2]->Fill(multTrkTOF, nTrk); 
    return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::AODPileupCheck ()
{
  Int_t isPileup = fAOD->IsPileupFromSPD(3);
  if (isPileup !=0 && fPeriod.EqualTo("LHC16t")) return false; // LHC16t : pPb
  if (fAOD->IsIncompleteDAQ()) return false;
  if (((AliAODHeader*)fAOD->GetHeader())->GetRefMultiplicityComb08() < 0) return false;
  if (fPeriod.EqualTo("LHC15o")){
    AliMultSelection* fMultSel = (AliMultSelection*)InputEvent()->FindListObject("MultSelection");
    if(!fMultSel->GetThisEventIsNotPileup()) return false;
    if(!fMultSel->GetThisEventIsNotPileupMV()) return false;
    if(!fMultSel->GetThisEventIsNotPileupInMultBins()) return false;
    if(!fMultSel->GetThisEventHasNoInconsistentVertices()) return false;
    if(!fMultSel->GetThisEventPassesTrackletVsCluster()) return false;
    if(!fMultSel->GetThisEventIsNotIncompleteDAQ()) return false;
    if(!fMultSel->GetThisEventHasGoodVertex2016()) return false;
  }
  return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::PileUpMultiVertex()
{
  // check for multi-vertexer pile-up
  const int    kMinPlpContrib = 5;
  const double kMaxPlpChi2    = 5.0;
  const double kMinWDist      = 15;

  const AliVVertex* vtPrm = 0;
  const AliVVertex* vtPlp = 0;

  int nPlp = 0;

  if(!(nPlp=fAOD->GetNumberOfPileupVerticesTracks()))
  return false;

  vtPrm = fAOD->GetPrimaryVertex();
  if(vtPrm == fAOD->GetPrimaryVertexSPD())
  return true;  // there are pile-up vertices but no primary

  //int bcPrim = vtPrm->GetBC();

  for(int ipl=0;ipl<nPlp;ipl++) {
    vtPlp = (const AliVVertex*)fAOD->GetPileupVertexTracks(ipl);
    if (vtPlp->GetNContributors() < kMinPlpContrib) continue;
    if (vtPlp->GetChi2perNDF()    > kMaxPlpChi2)    continue;
    //int bcPlp = vtPlp->GetBC();
    //if (bcPlp!=AliVTrack::kTOFBCNA && TMath::Abs(bcPlp-bcPrim)>2)
    // return kTRUE; // pile-up from other BC

    double wDst = GetWDist(vtPrm,vtPlp);
    if (wDst<kMinWDist)        continue;

    return true; // pile-up: well separated vertices
  }
  return false;
}

//---------------------------------------------------

double AliAnalysisTaskLambdaProtonCVE::GetWDist(const AliVVertex* v0, const AliVVertex* v1)
{
    // calculate sqrt of weighted distance to other vertex
    if (!v0 || !v1) {
        printf("One of vertices is not valid\n");
        return 0;
    }
    static TMatrixDSym vVb(3);
    double dist = -1;
    double dx = v0->GetX()-v1->GetX();
    double dy = v0->GetY()-v1->GetY();
    double dz = v0->GetZ()-v1->GetZ();
    double cov0[6],cov1[6];
    v0->GetCovarianceMatrix(cov0);
    v1->GetCovarianceMatrix(cov1);
    vVb(0,0) = cov0[0]+cov1[0];
    vVb(1,1) = cov0[2]+cov1[2];
    vVb(2,2) = cov0[5]+cov1[5];
    vVb(1,0) = vVb(0,1) = cov0[1]+cov1[1];
    vVb(0,2) = vVb(1,2) = vVb(2,0) = vVb(2,1) = 0.;
    vVb.InvertFast();
    if (!vVb.IsValid()) {printf("Singular Matrix\n"); return dist;}
    dist = vVb(0,0)*dx*dx + vVb(1,1)*dy*dy + vVb(2,2)*dz*dz
        +    2*vVb(0,1)*dx*dy + 2*vVb(0,2)*dx*dz + 2*vVb(1,2)*dy*dz;
    return dist>0 ? TMath::Sqrt(dist) : -1;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RemovalForLHC18 ()
{}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::RemovalForpPb ()
{}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::AcceptAODTrack(AliAODTrack *track)
{
    //------------------
    // track cut  
    //------------------
    double pt     = track->Pt();
    double eta    = track->Eta();
    int    nhits  = track->GetTPCNcls();
    double dedx   = track->GetTPCsignal();
    double chi2   = track->Chi2perNDF();
    int    charge = track->Charge();
    hEta[0]->Fill(eta);
    hNhits[0]->Fill(nhits);
    if(pt < fPtMin || pt > fPtMax || fabs(eta)>fEtaCut || fabs(nhits)<fNclsCut || chi2<fChi2Min || chi2>fChi2Max || dedx<fDedxCut) return false;
    hPt->Fill(pt);
    hEta[1]->Fill(eta);
    hNhits[1]->Fill(nhits);
    hPDedx->Fill(track->P()*charge, dedx);
    if (fPeriod.EqualTo("LHC11h") || fPeriod.EqualTo("LHC10h")){
      //------------------
      // dca cut
      //------------------
      double mag = fAOD->GetMagneticField(); 
      double dcaxy  = 999.;
      double dcaz   = 999.;
      double r[3];
      double dca[2];
      double cov[3];
      double vx    = fVtx->GetX();
      double vy    = fVtx->GetY();
      double vz    = fVtx->GetZ();
      bool proptodca = track->PropagateToDCA(fVtx, mag, 100., dca, cov);
      if (track->GetXYZ(r)) {
        dcaxy = r[0];
        dcaz  = r[1];
      } else {
        double dcax = r[0] - vx;
        double dcay = r[1] - vy;
        dcaz  = r[2] - vz;
        dcaxy = sqrt(dcax*dcax + dcay*dcay);
        // dcaxy = dca[0];
      }
      hDcaXy[0]->Fill(dcaxy);
      if (fabs(dcaxy)>fDcaCutxy) return false;
      hDcaXy[1]->Fill(dcaxy);
      hDcaZ[0]->Fill(dcaz);
      if (fabs(dcaz)>fDcaCutz) return false;
      hDcaZ[1]->Fill(dcaz);     
    }

    return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::GetV0CalibHist()
{
  if (fPeriod.EqualTo("LHC10h") ){
      for(int iCh = 0; iCh < 64; ++iCh) {
        fMultV0Ch[iCh] = hMultV0Read->GetBinContent(iCh+1, fRunNumBin+1);
      } 
      for(int i = 1; i < 3; ++i) {   // [0]: M; [1]: C; [2]: A;
        fV0XMean[i] = pV0XMeanRead[i]->GetBinContent(fRunNumBin+1, fCentBin+1, fVzBin+1);
        fV0YMean[i] = pV0YMeanRead[i]->GetBinContent(fRunNumBin+1, fCentBin+1, fVzBin+1);
      }    
      return true;
  } else if (fPeriod.EqualTo("LHC15o") ){ // A.Dobrin's V0Calib; "calibV0HIR.root"
      for(int iCh = 0; iCh < 64; ++iCh) {
        fMultV0Ch[iCh] = hMultV0->GetBinContent(iCh+1);
      } 
      // AliCentrality* centrality = ((AliAODHeader*)fAOD->GetHeader())->GetCentralityP();
      // Double_t centSPD = centrality->GetCentralityPercentile("CL1");
      AliMultSelection* fMultSelection = (AliMultSelection*) InputEvent()->FindListObject("MultSelection");
      if(!fMultSelection) {
        printf("\n\n **WARNING** ::UserExec() AliMultSelection object not found.\n\n");
        exit(1);
      }
      Double_t centrCL1 = fMultSelection->GetMultiplicityPercentile("CL1");
      Int_t iCentSPD = (Int_t)centrCL1;
      if (iCentSPD >= 90) return false;
      fV0XMean[0] = -999.; fV0YMean[0] = -999.; 
      for(int i = 0; i < 2; ++i) {   // [1]: C; [2]: A;
        fV0XMean[i+1] = hQx2mV0[i]->GetBinContent(iCentSPD+1);
        fV0YMean[i+1] = hQy2mV0[i]->GetBinContent(iCentSPD+1);
      }   
  }
  else return false;
  return true;
}

//---------------------------------------------------

bool AliAnalysisTaskLambdaProtonCVE::GetVZEROPlane()
{
  if (!GetV0CalibHist()) return false;
  double qxGE[3] = {0}, qyGE[3] = {0}, qxRecenter[3] = {0}, qyRecenter[3] = {0}; 
  double multRingGE[3] = {0};
  // [0]: M; [1]: C; [2]: A;
  for(int iCh = 0; iCh < 64; ++iCh) {
    if (TMath::IsNaN(fMultV0Ch[iCh]) || fMultV0Ch[iCh]<=0) continue;

    double phi = TMath::Pi()/8. + TMath::Pi()/4.*(iCh%8);
    double multCh = 0.;
    // double multCh = fAOD->GetVZEROEqMultiplicity(iCh);
    if (fPeriod.EqualTo("LHC10h") || fPeriod.EqualTo("LHC11h")) multCh= fAOD->GetVZEROEqMultiplicity(iCh);
    else if (fPeriod.EqualTo("LHC15o")) {
      AliAODVZERO* aodV0 = fAOD->GetVZEROData();
      multCh = aodV0->GetMultiplicity(iCh);
    }
    if (iCh<32) { // C
      double multChGEC = -1;
      if (iCh < 8)
          multChGEC = multCh/fMultV0Ch[iCh] * fMultV0Ch[0];
      else if (iCh >= 8 && iCh < 16)
          multChGEC = multCh/fMultV0Ch[iCh] * fMultV0Ch[8];
      else if (iCh >= 16 && iCh < 24)
          multChGEC = multCh/fMultV0Ch[iCh] * fMultV0Ch[16];
      else if (iCh >= 24 && iCh < 32)
          multChGEC = multCh/fMultV0Ch[iCh] * fMultV0Ch[24];
      if (multChGEC<0 || TMath::IsNaN(multChGEC)) continue;

      qxGE[1] += multChGEC*TMath::Cos(2*phi);
      qyGE[1] += multChGEC*TMath::Sin(2*phi);
      multRingGE[1] += multChGEC;
      qxGE[0] += multChGEC*TMath::Cos(2*phi);
      qyGE[0] += multChGEC*TMath::Sin(2*phi); 
      multRingGE[0] += multChGEC;        
    } else if (iCh>=32 && iCh<64) { // A
      double multChGEA = -1;
      if (iCh >= 32 && iCh < 40)
          multChGEA = multCh/fMultV0Ch[iCh] * fMultV0Ch[32];
      else if (iCh >= 40 && iCh < 48)
          multChGEA = multCh/fMultV0Ch[iCh] * fMultV0Ch[40];
      else if (iCh >= 48 && iCh < 56)
          multChGEA = multCh/fMultV0Ch[iCh] * fMultV0Ch[48];
      else if (iCh >= 56 && iCh < 64)
          multChGEA = multCh/fMultV0Ch[iCh] * fMultV0Ch[56];
      if (multChGEA<0 || TMath::IsNaN(multChGEA)) continue;

      qxGE[2] += multChGEA*TMath::Cos(2*phi);
      qyGE[2] += multChGEA*TMath::Sin(2*phi);
      multRingGE[2] += multChGEA;  
      qxGE[0] += multChGEA*TMath::Cos(2*phi);
      qyGE[0] += multChGEA*TMath::Sin(2*phi); 
      multRingGE[0] += multChGEA;
    }
  }
  if (multRingGE[0] < 1e-6 || multRingGE[1] < 1e-6) return false;
  double Qn_thisEvt[3];
  double psiRecenter[3];
  for (int i = 1; i < 3; ++i) {
      Qn_thisEvt[i] = -1;
      double qxMean = fV0XMean[i];
      double qyMean = fV0YMean[i];   
      if (TMath::IsNaN(qxMean) || TMath::IsNaN(qyMean)) continue;
      if (qyMean < -900 || qxMean < -900) continue; 
      // For 10 h, we've stored the qx/y of V0M, and they cannot been found in A.Dorbin's calib file for 15o period!
      qxRecenter[i] = qxGE[i] - qxMean;
      qyRecenter[i] = qyGE[i] - qyMean;
      Qn_thisEvt[i] = sqrt(qxRecenter[i]*qxRecenter[i] + qyRecenter[i]*qyRecenter[i])/ sqrt(multRingGE[i]);
      hQnCentRecenter[i]->Fill(fCent, Qn_thisEvt[i]);
      // psiRecenter
      psiRecenter[i] = GetEventPlane(qxRecenter[i], qyRecenter[i],2.);
      hPsiV0Recenter[fCentBin][i]->Fill(psiRecenter[i]); 
      if (fQAV0){
        double vz    = fVtx->GetZ();  
        double centSPD  =0.;
        if (fPeriod.EqualTo("LHC15o")){
          AliMultSelection* fMultSelection = (AliMultSelection*) InputEvent()->FindListObject("MultSelection");
          centSPD = fMultSelection->GetMultiplicityPercentile("CL1");
        }
        else if (fPeriod.EqualTo("LHC11h") || fPeriod.EqualTo("LHC10h") ){
          centSPD =  fAOD->GetCentrality()->GetCentralityPercentile("CL1");
        }
        hQxCentRecenter[i]->Fill(centSPD, qxRecenter[i]);
        hQyCentRecenter[i]->Fill(centSPD, qyRecenter[i]);
        hQxVtxRecenter[i]->Fill(vz, qxRecenter[i]);
        hQyVtxRecenter[i]->Fill(vz, qyRecenter[i]);
      }   
  }

  if (Qn_thisEvt[1]<0) return false; // V0C
  fPsi2V0M = psiRecenter[0];
  fPsi2V0C = psiRecenter[1];
  fPsi2V0A = psiRecenter[2];

  return true;
}

//---------------------------------------------------

Bool_t AliAnalysisTaskLambdaProtonCVE::IsGoodV0(AliAODv0 *aodV0) 
{
  if (!aodV0) {
    AliError(Form("ERROR: Could not retrieve aodV0"));
    return kFALSE;
  }
  // Offline reconstructed V0 only
  if ( aodV0->GetOnFlyStatus() ) return kFALSE;
  // Get daughters and check them     
  AliAODTrack *myTrackNegTest = dynamic_cast<AliAODTrack *>(aodV0->GetDaughter(1));
  AliAODTrack *myTrackPosTest = dynamic_cast<AliAODTrack *>(aodV0->GetDaughter(0));
  if (!myTrackPosTest || !myTrackNegTest) {
    Printf("strange analysis::UserExec:: Error:Could not retreive one of the daughter track\n");
    return kFALSE;
  }
  // Unlike signs of daughters
  if ( myTrackNegTest->Charge() == myTrackPosTest->Charge() ) return kFALSE;
  // Cosinus of pointing angle      
  double dCPA = aodV0->CosPointingAngle(fVetex);
  // cut on Cosinus of pointing angle
  if ( dCPA < fV0CPAMin ) return kFALSE;
  // DCA of V0
  double dV0Dca = aodV0->DcaV0ToPrimVertex();
  if ( TMath::Abs(dV0Dca) > fV0DCAToPrimVtxMax ) return kFALSE;
  // V0 path length before decay
  double dDecayLength = aodV0->DecayLengthV0(fVetex);
  if ( dDecayLength > fV0DecayLengthMax ) return kFALSE;
  if ( dDecayLength < fV0DecayLengthMin ) return kFALSE;
  // DCA between daughters
  double dDCA = aodV0->DcaV0Daughters();
  if ( dDCA > fV0DcaBetweenDaughtersMax ) return kFALSE;
  double dPt = aodV0->Pt();
  if( dPt < fV0PtMin ) return kFALSE;
  double dRapidity = aodV0->RapLambda();
  if( TMath::Abs(dRapidity) > fV0RapidityMax ) return kFALSE;
  return kTRUE;
}



Bool_t AliAnalysisTaskLambdaProtonCVE::IsGoodDaughterTrack(const AliAODTrack *track)
{
  // TPC refit
  if (!track->IsOn(AliAODTrack::kTPCrefit)) return kFALSE;
  //No kinks
  if(Int_t(track->GetProdVertex()->GetType()) == AliAODVertex::kKink) return kFALSE;
  // Maximum value of transverse momentum 
  double dPt = track->Pt();
  if (dPt > fDaughtersPtMax) return kFALSE;
  // Maximum value of pseudorapidity
  double dEta = track->Eta();
  if (TMath::Abs(dEta) > fDaughtersEtaMax) return kFALSE;
  // Minimum number of clusters
  float nCrossedRowsTPC = track->GetTPCClusterInfo(2,1);
  if (nCrossedRowsTPC < fDaughtersTPCNclsMin) return kFALSE;
  // Findable clusters > 0
  int findable = track->GetTPCNclsF();
  if (findable <= 0) return kFALSE;
  // [number of crossed rows]>0.8  [number of findable clusters].
  if (nCrossedRowsTPC/findable < 0.8) return kFALSE;
  return kTRUE;
}

Int_t AliAnalysisTaskLambdaProtonCVE::GetLambdaCode(const AliAODTrack *pTrack, const AliAODTrack *nTrack) 
{

  Bool_t IsLambda     = kFALSE;
  Bool_t IsAntiLambda = kFALSE;
  Int_t  code = 0;

  //Λ-->(p+)+(π-)
  Float_t nSigTPCPosProton = TMath::Abs(fPIDResponse->NumberOfSigmasTPC(pTrack,AliPID::kProton));//TPC p+
  Float_t nSigTPCNegPion   = TMath::Abs(fPIDResponse->NumberOfSigmasTPC(nTrack,AliPID::kPion));//TPC π-
  //(Λ-)-->(p-)+(π+)
  Float_t nSigTPCPosPion   = TMath::Abs(fPIDResponse->NumberOfSigmasTPC(pTrack,AliPID::kPion));//TPC π+
  Float_t nSigTPCNegProton = TMath::Abs(fPIDResponse->NumberOfSigmasTPC(nTrack,AliPID::kProton));//TPC p-

  IsLambda = (nSigTPCPosProton < fV0PosProtonTPCNsigma) && (nSigTPCNegPion < fV0NegPionTPCNsigma);
  IsAntiLambda = (nSigTPCNegProton < fV0NegProtonTPCNsigma) && (nSigTPCPosPion < fV0PosPionTPCNsigma);

  if (fV0DaughterUseTOF)
  {
    Float_t nSigTOFPosProton = TMath::Abs(fPIDResponse->NumberOfSigmasTOF(pTrack,AliPID::kProton));//TOF p+
    Float_t nSigTOFNegPion   = TMath::Abs(fPIDResponse->NumberOfSigmasTOF(nTrack,AliPID::kPion));//TOF π-
    Float_t nSigTOFPosPion   = TMath::Abs(fPIDResponse->NumberOfSigmasTOF(pTrack,AliPID::kPion));//TOF π+
    Float_t nSigTOFNegProton = TMath::Abs(fPIDResponse->NumberOfSigmasTOF(nTrack,AliPID::kProton));//TOF p-

    IsLambda *= (nSigTOFPosProton < fV0PosProtonTOFNsigma && nSigTOFNegPion < fV0NegPionTOFNsigma);
    IsAntiLambda *= (nSigTOFNegProton < fV0NegProtonTOFNsigma && nSigTOFPosPion < fV0PosPionTOFNsigma);
  }
  
  if (IsLambda)     code =  3122;
  if (IsAntiLambda) code = -3122;
  if (IsLambda && IsAntiLambda) code = 0;

  return code;
}

Bool_t AliAnalysisTaskLambdaProtonCVE::CheckPIDofParticle(AliAODTrack* ftrack,Int_t pidToCheck){
  
  if(pidToCheck==0) return kTRUE;    //// Charge Particles do not need PID check
  
  Bool_t bPIDokay = kFALSE;

  if(!fPIDResponse){
    Printf("\n Could Not access PIDResponse Task, please Add the Task...\n return with kFALSE pid\n");
    return kFALSE;
  }

  /// Rihan todo: To set the low pT cuts for nSigmaTPC from AddTaskMacro!
  /// Although someone barely needs to change it given the purity..
  
  Double_t nSigTPC = 0, nSigTOF = 0, nSigRMS = 0;
  Double_t trkPtPID  = ftrack->Pt();
  Int_t trkChargePID = ftrack->Charge();

  ///Pion => 
  if(pidToCheck==1){ 
    nSigTPC = fPIDResponse->NumberOfSigmasTPC(ftrack, AliPID::kPion);//Some warning show here (***TDatabasePDG::AddParicle: particle with PDGcode = 3124 already defind),I don't understand what happended. --chunzheng
    nSigTOF = fPIDResponse->NumberOfSigmasTOF(ftrack, AliPID::kPion);
    nSigRMS = TMath::Sqrt(nSigTPC*nSigTPC + nSigTOF*nSigTOF);

    if(trkPtPID<=0.5 && TMath::Abs(nSigTPC)<=fNSigmaTPCCut){
      bPIDokay = kTRUE;
    }
    // Using TPCTOF RMS cut for higher pt: 
    else if(trkPtPID>0.5 && TMath::Abs(nSigRMS)<=fNSigmaTOFCut){ 
      bPIDokay = kTRUE;
    }
    return bPIDokay;
  }
  ///Kaon => 
  else if(pidToCheck==2){
    nSigTPC = fPIDResponse->NumberOfSigmasTPC(ftrack, AliPID::kKaon);	
    nSigTOF = fPIDResponse->NumberOfSigmasTOF(ftrack, AliPID::kKaon);
    nSigRMS = TMath::Sqrt(nSigTPC*nSigTPC + nSigTOF*nSigTOF);
	
    if(trkPtPID<=0.45 && TMath::Abs(nSigTPC)<=fNSigmaTPCCut){
      bPIDokay = kTRUE;
    }
    else if(trkPtPID>0.45 && TMath::Abs(nSigRMS)<=fNSigmaTOFCut){
      bPIDokay = kTRUE;
    }
    return bPIDokay;
  }
  ///proton => 
  else if(pidToCheck==3){///
    nSigTPC = fPIDResponse->NumberOfSigmasTPC(ftrack, AliPID::kProton);    
    nSigTOF = fPIDResponse->NumberOfSigmasTOF(ftrack, AliPID::kProton);
    nSigRMS = TMath::Sqrt(nSigTPC*nSigTPC + nSigTOF*nSigTOF);
	
    if(trkPtPID<=0.6 && TMath::Abs(nSigTPC)<=fNSigmaTPCCut){
      bPIDokay = kTRUE;
      if(trkChargePID>0 && trkPtPID<0.4) bPIDokay = kFALSE;  
    }
    else if(trkPtPID>0.6 && TMath::Abs(nSigRMS)<=fNSigmaTOFCut){
      bPIDokay = kTRUE;
    }
    return bPIDokay;
  }
  else{
    Printf("\n -Ve number not allowed! Choose among: 0,1,2,3,4  (Charge Pion, Kaon, Proton, Lambda)\n return with kFALSE \n");
    return kFALSE;
  }
  
  return kFALSE;
}
void AliAnalysisTaskLambdaProtonCVE::OpenInfoCalibration(Int_t run)
{
  if (!gGrid) {
      TGrid::Connect("alien://");
  }
  TFile* fileV0Calib = NULL;
  if (fPeriod.EqualTo("LHC15o")) fileV0Calib = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc15o/calibV015oP2.root");
  if (fPeriod.EqualTo("LHC11h")) fileV0Calib = TFile::Open("alien:///alice/cern.ch/user/w/wenya/refData/reflhc11h/calibV011h_2P2.root");
  if(!fileV0Calib){
      printf("OADB V0 calibration file cannot be opened\n");
      return;
  }
  // Mult
  AliOADBContainer* contMult = (AliOADBContainer*) fileV0Calib->Get("hMultV0BefCorPfpx");
  if(!contMult){
      printf("OADB object hMultV0BefCorr is not available in the file\n");
      return;
  }
  // V0C Qx Mean 
  AliOADBContainer* contQxncm = (AliOADBContainer*) fileV0Calib->Get(Form("fqxc%im",2));
  if(!contQxncm){
      printf("OADB object fqxcnm is not available in the file\n");
      return;
  }
  // V0C Qy Mean 
  AliOADBContainer* contQyncm = (AliOADBContainer*) fileV0Calib->Get(Form("fqyc%im",2));
  if(!contQyncm){
      printf("OADB object fqycnm is not available in the file\n");
      return;
  }
  // V0A Qx Mean 
  AliOADBContainer* contQxnam = (AliOADBContainer*) fileV0Calib->Get(Form("fqxa%im",2));
  if(!contQxnam){
      printf("OADB object fqxanm is not available in the file\n");
      return;
  }
  // V0A Qy Mean 
  AliOADBContainer* contQynam = (AliOADBContainer*) fileV0Calib->Get(Form("fqya%im",2));
  if(!contQynam){
      printf("OADB object fqyanm is not available in the file\n");
      return;
  }
  // Mult   
  if(!(contMult->GetObject(run) ) ){
      printf("OADB object hMultV0BefCorPfpx is not available for run %i\n", run);
      return;
  }
  hMultV0 = ((TH1D*) contMult->GetObject(run ) );
  // V0C Qx Mean 
  if(!(contQxncm->GetObject(run) ) ){
      printf("OADB object fqxcnm is not available for run %i\n", run);
      return;
  }
  hQx2mV0[0] = ((TH1D*) contQxncm->GetObject(run) );
  // V0C Qy Mean 
  if(!(contQyncm->GetObject(run) ) ){
      printf("OADB object fqycnm is not available for run %i\n", run);
      return;
  }
  hQy2mV0[0] = ((TH1D*) contQyncm->GetObject(run) );
  // V0A Qx Mean
  if(!(contQxnam->GetObject(run) ) ){
      printf("OADB object fqxanm is not available for run %i\n", run);
      return;
  }
  hQx2mV0[1] = ((TH1D*) contQxnam->GetObject(run) );
  // V0A Qy Mean
  if(!(contQynam->GetObject(run) ) ){
      printf("OADB object fqyanm is not available for run %i\n", run);
      return;
  }
  hQy2mV0[1] = ((TH1D*) contQynam->GetObject(run) );    
}
