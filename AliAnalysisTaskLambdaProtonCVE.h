#ifndef AliAnalysisTaskLambdaProtonCVE_cxx
#define AliAnalysisTaskLambdaProtonCVE_cxx
#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"
#include "AliAODTrack.h"
#include "AliPIDResponse.h"
#include "AliAODv0.h"
#include "TProfile3D.h"
#include "TProfile2D.h"
#include "TProfile.h"
#include "TComplex.h"
#include "TList.h"
#include "TFile.h"
#include "TSpline.h"
#include "TProfile.h"
#include "TH1.h"
#include "TH2.h"

//class AliAnalysisUtils;

#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"

class AliAnalysisTaskLambdaProtonCVE : public AliAnalysisTaskSE
{
public:

  AliAnalysisTaskLambdaProtonCVE();
  AliAnalysisTaskLambdaProtonCVE(const char *name);
  AliAnalysisTaskLambdaProtonCVE(const char *name, TString PR, bool NUE, bool NUA, bool V0Calib);

  virtual ~AliAnalysisTaskLambdaProtonCVE();

  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *option);
  virtual void Terminate(Option_t *);

  void SetDebug(int debug)               {this->fDebug             = debug;}
  void SetTrigger(TString trigger)       {this->fTrigger         = trigger;}
  void SetFilterBit(int fltbit)          {this->fFltbit           = fltbit;}
  void SetNclsCut(int nclsCut)           {this->fNclsCut         = nclsCut;}
  void SetChi2Max(float chi2Max)         {this->fChi2Max         = chi2Max;}
  void SetChi2Min(float chi2Min)         {this->fChi2Min         = chi2Min;}
  void SetDCAcutZ(float dcaCutz)         {this->fDcaCutz         = dcaCutz;}
  void SetDCAcutXY(float dcaCutxy)       {this->fDcaCutxy       = dcaCutxy;}
  void SetPtMin(float ptMin)             {this->fPtMin             = ptMin;}
  void SetPtMax(float ptMax)             {this->fPtMax             = ptMax;}
  void SetProtonPtMin(float protonPtMin) {this->fPtMin       = protonPtMin;}
  void SetProtonPtMax(float protonPtMax) {this->fPtMax       = protonPtMax;}
  void SetPeriod(TString period)         {this->fPeriod           = period;}
  void SetMultComp(TString multComp)     {this->fMultComp       = multComp;}
  void SetV0CalibOn(bool V0CalibOn)      {this->fV0CalibOn     = V0CalibOn;}
  void SetTPCCalibOn(bool TPCCalibOn)    {this->fTPCCalibOn   = TPCCalibOn;}
  void SetV0QAOn(bool QAV0)              {this->fQAV0               = QAV0;}
  void SetNUEOn(bool doNUE)              {this->fDoNUE             = doNUE;}
  void SetNUAOn(bool doNUA)              {this->fDoNUA             = doNUA;}
  void SetCentCut(float centDiffCut)     {this->fCentDiffCut = centDiffCut;}

  //V0 Chun zheng: Cuts on V0 and its daughters
  void SetV0PtMin(double v0PtMin)                                   {this->fV0PtMin                                   = v0PtMin;}
  void SetV0CPAMin(double v0CPAMin)                                 {this->fV0CPAMin                                 = v0CPAMin;}
  void SetV0RapidityMax(double v0RapidityMax)                       {this->fV0RapidityMax                       = v0RapidityMax;}
  void SetV0DecayLengthMax(double v0DecayLengthMax)                 {this->fV0DecayLengthMax                 = v0DecayLengthMax;}
  void SetV0DecayLengthMin(double v0DecayLengthMin)                 {this->fV0DecayLengthMin                 = v0DecayLengthMin;}
  void SetV0DCAToPrimVtxMax(double v0DCAToPrimVtxMax)               {this->fV0DCAToPrimVtxMax               = v0DCAToPrimVtxMax;}
  void SetV0DcaBetweenDaughtersMax(double v0DcaBetweenDaughtersMax) {this->fV0DcaBetweenDaughtersMax = v0DcaBetweenDaughtersMax;}
  //V0 Daughter Cut
  void SetDaughtersPIDUseTOF(bool daughterPIDUseTOF)                {this->fV0DaughterUseTOF                = daughterPIDUseTOF;}
  void SetDaughtersPtMax(double daughtersPtMax)                     {this->fDaughtersPtMax                     = daughtersPtMax;}
  void SetDaughtersEtaMax(double daughtersEtaMax)                   {this->fDaughtersEtaMax                   = daughtersEtaMax;}
  void SetDaughtersNsigma(double daughtersNsigma)                   {this->fDaughtersNsigma                   = daughtersNsigma;}
  void SetDaughtersTPCNclsMin(double daughtersTPCNclsMin)           {this->fDaughtersTPCNclsMin           = daughtersTPCNclsMin;}
  void SetDaughtersDCAToPrimVtxMin(double daughtersDCAToPrimVtxMin) {this->fDaughtersDCAToPrimVtxMin = daughtersDCAToPrimVtxMin;}
  //Lambda Mass Cut
  void SetMassMean(double massMean)                                 {this->fMassMean                                 = massMean;}
  void SetLambdaMassCut(double lambdaMassCut)                       {this->fLambdaMassCut                       = lambdaMassCut;}
  //Check PID Flow
  void IsCheckPIDFlow(bool checkPIDFlow)                            {this->bCheckPIDFlow                         = checkPIDFlow;}



private:

  double      GetNUECor(int charge, double pt);
  double      GetNUACor(int charge, double phi, double eta, double vz);
  int         GetRunNumBin(int runNum);
  // pile-up
  bool        RejectEvtMultComp(AliAODEvent* fAOD);
  bool        RejectEvtTFFit(AliAODEvent* fAOD);
  bool        RejectEvtTPCITSfb32TOF(AliAODEvent* fAOD);
  bool        AODPileupCheck(AliAODEvent* fAOD);
  bool        PileUpMultiVertex (AliAODEvent* fAOD);
  double      GetWDist(const AliVVertex* v0, const AliVVertex* v1);
  bool        RemovalForLHC18(AliAODEvent* fAOD);
  bool        RemovalForRun1 (AliAODEvent* fAOD, AliAnalysisUtils* fUtils);
  bool        RemovalForpPb(AliAODEvent* fAOD);
  bool        AcceptAODTrack(AliAODEvent* fAOD, AliAODTrack *track, AliAODVertex* fVtx);
  bool        GetV0CalibHist(AliAODEvent* fAOD, AliAODVertex* fVtx);
  double      GetEventPlane(double qx, double qy, double harmonic);
  bool        AnalyzeAOD();
  bool        GetVZEROPlane();
  void        OpenInfoCalibration(Int_t run);

  // Cuts and options
  int                       fDebug; // debug level controls amount of output statements
  TString                 fTrigger; //
  int                      fFltbit; // AOD filter bit selection
  int                     fNclsCut; // ncls cut for all tracks 
  float                   fChi2Max; // upper limmit for chi2
  float                   fChi2Min; // lower limmit for chi2
  float                   fDcaCutz; // dcaz cut for all tracks
  float                  fDcaCutxy; // dcaxy cut for all tracks
  float                     fPtMin; // minimum pt for Q-vector components
  float                     fPtMax; // maximum pt for Q-vector components
  TString                  fPeriod; // period
  TString                fMultComp; // Multiplicity Comparison pile-up
  double           fEtaGapPosforEP; // value for the Eta Gap Pos
  double           fEtaGapNegforEP;
  bool                  fV0CalibOn; // switch for v0 qn calib
  bool                 fTPCCalibOn; // switch for tpc qn calib
  bool                       fQAV0; // flag for V0  qn QA
  bool                      fDoNUE; // switch for NUE
  bool                      fDoNUA; // switch for NUA
  float               fCentDiffCut; // centrality restriction for V0M and TRK
  // Global Variables Unchanged in an Evt
  int                      fRunNum; // runnumber
  int                   fRunNumBin; // runnumer bin; 10:139510...; 11:170387...; 15HIR:246994...
  int                       fVzBin; // vertex z bin
  int                     fCentBin; // centrality bin: 0-10
  double                     fCent; // value of centrality 
  const float              fEtaCut; // eta cut
  const float             fDedxCut; // dedx cut
  const float             fZvtxCut; // z-vertex selection for collision
  int                     fPUSyst;
  // PID Sigma
  float               fProtonPtMin; // minimum proton pt for Lambda-Proton Pair
  float               fProtonPtMax; // maximum proton pt for Lambda-Proton Pair
  double             fNSigmaTPCCut;
  double             fNSigmaTOFCut;
  bool               bCheckPIDFlow;

  // Weight List
  TList*                fListNUE; // read list for NUE
  TList*                fListNUA; // read lists for NUA
  TList*                fListVZEROCALIB; // read list fpr V0 Calib

  // Handles
  AliAODEvent*          fAOD;         //! aod Event
  AliPIDResponse*       fPIDResponse; //! PID Handler
  AliAnalysisUtils*     fUtils;       //! Event Selection Options
  AliAODVertex*         fVtx;
  double                fVetex[3];

    // Read Files for NUA/NUE/VoCalib
    TH1D*             hNUEweightPlus;
    TH1D*             hNUEweightMinus;
    TH2D*             hNUAweightPlus;
    TH2D*             hNUAweightMinus;
    TH3F*             hCorrectNUAPos; // Protty
    TH3F*             hCorrectNUANeg; // Protty
    TH2D*             hMultV0Read;
    TF1*              fSPDCutPU;
    TF1*              fV0CutPU;
    TF1*              fCenCutLowPU;
    TF1*              fCenCutHighPU;
    TF1*              fMultCutPU;
    // Output QA
    TList*            fOutputList;          
    TH1D*             hEvtCount;   
    TH1I*             hRunNumBin;  
    TH1D*             hPt;
    TH2D*             hPDedx;

    // Read Files for V0Calib
    TProfile3D*       pV0XMeanRead[3]; 
    TProfile3D*       pV0YMeanRead[3];
    // Run2 A.Dorbin
    TH1D*             hMultV0; //Dobrin
    TH1D*             hQx2mV0[2];
    TH1D*             hQy2mV0[2];
    double            fMultV0Ch[64];
    double            fV0XMean[3];
    double            fV0YMean[3];

    // Output QA
    TH1D*             hCent[2];
    TH1D*             hVz[2];
    TH2D*             hCentQA[8];
    TH2D*             hMultCentQA[2];
    TH2D*             hMultMultQA[6];

    // track-wise QA
    TH1D*             hEta[2];
    TH1D*             hPhi[2];
    TH2D*             hEtaPhi[2];
    TH1D*             hDcaXy[2];
    TH1D*             hDcaZ[2];
    TH1D*             hNhits[2];

    // Qn & psi QA
    TH2D*             hQxCentRecenter[3];
    TH2D*             hQxVtxRecenter[3];
    TH2D*             hQyCentRecenter[3];
    TH2D*             hQyVtxRecenter[3];
    TH2D*             hQnCentRecenter[3];
    TH1D*             hPsiV0Recenter[10][3];
    double            fPsi2V0M;
    double            fPsi2V0C;
    double            fPsi2V0A;
    double            fPsi2TPCPos;
    double            fPsi2TPCNeg;

    TProfile*         hTPCPsi2Correlation;//!
    TProfile*         hV0CV0APsi2Correlation;     //!
    TProfile*         hV0CTPCPosPsi2Correlation;  //!
    TProfile*         hV0ATPCPosPsi2Correlation;  //!
    TProfile*         hV0CTPCNegPsi2Correlation;  //!
    TProfile*         hV0ATPCNegPsi2Correlation;  //!
  
  /// Chunzheng: V0 (Lambda) Cut parameters:
  double                   fV0PtMin; //!
  double                  fV0CPAMin; //!
  double             fV0RapidityMax; //!
  double          fV0DecayLengthMin; //!
  double          fV0DecayLengthMax; //!
  double         fV0DCAToPrimVtxMax; //!
  double  fV0DcaBetweenDaughtersMax; //!
  //V0 Daughter
  double            fDaughtersPtMax; //!
  double           fDaughtersNsigma; //!
  double           fDaughtersEtaMax; //!
  double       fDaughtersTPCNclsMin; //!
  double  fDaughtersDCAToPrimVtxMin; //!
  float       fV0PosProtonTPCNsigma; //!
  float         fV0NegPionTPCNsigma; //!
  float       fV0NegProtonTPCNsigma; //!
  float         fV0PosPionTPCNsigma; //!
  bool            fV0DaughterUseTOF; //!
  float       fV0PosProtonTOFNsigma; //!
  float         fV0NegPionTOFNsigma; //!
  float       fV0NegProtonTOFNsigma; //!
  float         fV0PosPionTOFNsigma; //!
  //Lambda Mass
  double                    fMassMean; //!
  double               fLambdaMassCut; //!

  /// chunzheng: V0 QA Histograms
  TH1D           *fHistV0Pt;              //! Raw V0s' pT
  TH1D           *fHistV0Eta;             //! Raw V0s' eta
  TH1D           *fHistV0DcatoPrimVertex; //! Raw V0s' DcatoPV
  TH1D           *fHistV0CPA;             //! Raw V0s' CPA(cosine pointing angle)
  TH1D           *fHistV0DecayLength;     //! Raw V0s' DecayLength

  ///Lambda-X correlators: Naming Style for Histograms ->
  /// Lambda = L-capital, Proton = P-capital, Anti= A-capital.
  TProfile       *fProfileDelta_Lambda_hPos; //!
  TProfile       *fProfileDelta_Lambda_hNeg; //!
  TProfile       *fProfileDelta_Lambda_Proton;     //!
  TProfile       *fProfileDelta_Lambda_AntiProton; //!
  TProfile       *fProfileDelta_AntiLambda_hPos; //!
  TProfile       *fProfileDelta_AntiLambda_hNeg; //!
  TProfile       *fProfileDelta_AntiLambda_Proton;     //!
  TProfile       *fProfileDelta_AntiLambda_AntiProton; //!
  TProfile       *fProfileGammaTPC_Lambda_hPos; //!
  TProfile       *fProfileGammaTPC_Lambda_hNeg; //!
  TProfile       *fProfileGammaTPC_Lambda_Proton;     //!
  TProfile       *fProfileGammaTPC_Lambda_AntiProton; //!
  TProfile       *fProfileGammaTPC_AntiLambda_hPos; //!
  TProfile       *fProfileGammaTPC_AntiLambda_hNeg; //!
  TProfile       *fProfileGammaTPC_AntiLambda_Proton;     //!
  TProfile       *fProfileGammaTPC_AntiLambda_AntiProton; //!
  
  TProfile       *fProfileGammaV0C_Lambda_hPos; //!
  TProfile       *fProfileGammaV0C_Lambda_hNeg; //!
  TProfile       *fProfileGammaV0C_Lambda_Proton;     //!
  TProfile       *fProfileGammaV0C_Lambda_AntiProton; //!
  TProfile       *fProfileGammaV0C_AntiLambda_hPos; //!
  TProfile       *fProfileGammaV0C_AntiLambda_hNeg; //!
  TProfile       *fProfileGammaV0C_AntiLambda_Proton;     //!
  TProfile       *fProfileGammaV0C_AntiLambda_AntiProton; //!

  TProfile       *fProfileGammaV0A_Lambda_hPos; //!
  TProfile       *fProfileGammaV0A_Lambda_hNeg; //!
  TProfile       *fProfileGammaV0A_Lambda_Proton;     //!
  TProfile       *fProfileGammaV0A_Lambda_AntiProton; //!
  TProfile       *fProfileGammaV0A_AntiLambda_hPos; //!
  TProfile       *fProfileGammaV0A_AntiLambda_hNeg; //!
  TProfile       *fProfileGammaV0A_AntiLambda_Proton;     //!
  TProfile       *fProfileGammaV0A_AntiLambda_AntiProton; //!

  /// chunzheng: Lambda QA Info
  TH1D             *fHistLambdaPt[2];      //! [0]:Before the Mass Cut [1]:After the Mass Cut
  TH1D             *fHistLambdaEta[2];     //!
  TH1D             *fHistLambdaPhi[2];
  TH1D             *fHistLambdaDcaToPrimVertex[2]; //!
  TH1D             *fHistLambdaCPA[2];     //!
  TH1D             *fHistLambdaDecayLength[2];     //!
  TH1D             *fHistLambdaMass[2];    //!
  TH1D             *fHistAntiLambdaPt[2];  //!
  TH1D             *fHistAntiLambdaEta[2]; //!
  TH1D             *fHistAntiLambdaPhi[2];
  TH1D             *fHistAntiLambdaDcaToPrimVertex[2]; //!
  TH1D             *fHistAntiLambdaCPA[2]; //!
  TH1D             *fHistAntiLambdaDecayLength[2]; //!
  TH1D             *fHistAntiLambdaMass[2];//!  
  TProfile         *fProfileLambdaMassVsPt[2];     //!
  TProfile         *fProfileAntiLambdaMassVsPt[2]; //!
  ///Check PID Flow
  TH3D             *fHist3DdNdPhiCentPthPos[3];
  TH3D             *fHist3DdNdPhiCentPthNeg[3];  
  TH3D             *fHist3DdNdPhiCentPtProton[3];
  TH3D             *fHist3DdNdPhiCentPtAntiProton[3];
  TH3D             *fHist3DdNdPhiCentPtLambda[4];
  TH3D             *fHist3DdNdPhiCentPtAntiLambda[4];

  //void  SetupLambdaPIDFlowHistograms();
  bool CheckPIDofParticle(AliAODTrack* ftrack,Int_t pidToCheck);

    ///// Chunzheng: V0 (Lambda)
  bool IsGoodV0(AliAODv0 *aodV0);
  bool IsGoodDaughterTrack(const AliAODTrack *track);

  // //FIXME
  // Double_t GetNUAWeightForTrack(Double_t fVtxZ=0,Double_t fPhi=0,Double_t fEta=0,Int_t gChrg=1);
  // Double_t GetNUAWeightForTrackPID(Double_t fVtxZ=0,Double_t fPhi=0,Double_t fEta=0,Int_t gChrg=1);
  // Double_t GetMCEfficiencyWeightForTrack(Double_t fPt=1.0,Int_t gChrg=1,Int_t kPID=0);
  Int_t    GetLambdaCode(const AliAODTrack *pTrack, const AliAODTrack *ntrack); 


  AliAnalysisTaskLambdaProtonCVE(const AliAnalysisTaskLambdaProtonCVE&);
  AliAnalysisTaskLambdaProtonCVE& operator=(const AliAnalysisTaskLambdaProtonCVE&);

  ClassDef(AliAnalysisTaskLambdaProtonCVE, 1);
};

#endif
