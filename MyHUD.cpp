/**
 Nick Zayatz, Michele Burns, and Bel LaPointe
 11/1/15
 
 CSC-4360: Tanks
 MyHUD.cpp
 **/

#include "Tanks.h"
#include "MyHUD.h"
#include "TankCharacter.h"
#include <cmath>

#define BUTTONTYPE_MAIN_RESTART 	1
#define BUTTONTYPE_MAIN_EXIT 		2

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);


const FColor AMyHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AMyHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AMyHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AMyHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AMyHUD::FColor_White = FColor(255, 255, 255, 255);

const FLinearColor AMyHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AMyHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AMyHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AMyHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);

const float healthWidth = 10;

AMyHUD::AMyHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    //PrimaryActorTick.bCanEverTick = true;
    
    //Draw HUD?
    DontDrawHUD = false;
    
    //States
    ConfirmDialogOpen = false;
    InMainMenu = true;
    won = false;
    MainMenuOn = false;
    
    //Scale
    GlobalHUDMult = 1;
    DefaultFontScale = 0.7;   //scaling down a size 36 font
    
    //	I recommend creating fonts at a high resolution / size like 36
    //	then you can scale down the font as needed to any size of your choice
    // this avoids needing to make multiple fonts for different sizes, but have a high
    // resolution when you use larger font sizes
    
}


// Draw Dialogs
void AMyHUD::DrawHUD_DrawDialogs()
{
    DrawMainMenuButtons();
    if (ConfirmDialogOpen) DrawConfirm();
}

void AMyHUD::DrawConfirm()
{
    //Blue rect with alpha 50%
    DrawHUDRect(Canvas->SizeX / 2 - 90, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(0, 0, 1, 0.2333));
    
    //Draw buttons
    DrawConfirmButtons();
}

//Buttons
void AMyHUD::DrawMainMenuButtons()
{
    //Start Point
    float xStart = 100;
    float yStart = 410;
    
    //Background
    VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120)); //alpha 120/255
    
    //Text
    DrawHUDText(
                VerdanaFont, "Restart", xStart + 20, yStart + 20,
                LC_Black, DefaultFontScale,
                true, LC_Yellow
                );
    
    //Clear buttons with ButtonsMain.Empty()
    if (ButtonsMain.Num() < 1)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_MAIN_RESTART;
        newButton.toolTip = "Restart the Game!";
        newButton.minX = xStart;
        newButton.maxX = xStart + 150;
        newButton.minY = yStart;
        newButton.maxY = yStart + 80;
        
        //Add to correct array
        ButtonsMain.Add(newButton);
    }
    
    
    xStart = 100;
    yStart = 510;
    
    VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120)); //alpha 120/255
    
    //Text
    DrawHUDText(
                VerdanaFont, "Exit", xStart + 45, yStart + 20,
                LC_Black, DefaultFontScale,
                true, LC_Yellow
                );
    
    if (ButtonsMain.Num() < 2)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_MAIN_EXIT;
        newButton.toolTip = "Exit the Game!";
        newButton.minX = xStart;
        newButton.maxX = xStart + 150;
        newButton.minY = yStart;
        newButton.maxY = yStart + 80;
        
        //Add to correct array
        ButtonsMain.Add(newButton);
    }
}
void AMyHUD::DrawConfirmButtons()
{
    float xStart = Canvas->SizeX / 2 - 100;
    float yStart = Canvas->SizeY / 2 - 40;
    
    //Highlighted?
    if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Red;
    else ColorPtr = &LC_Yellow;
    
    //Text
    DrawHUDText(
                VerdanaFont, "Yes", xStart + 30, yStart + 20,
                *ColorPtr, DefaultFontScale,
                true
                );
    
    if (ButtonsConfirm.Num() < 1)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_CONFIRM_YES;
        newButton.toolTip = "";
        newButton.minX = xStart;
        newButton.maxX = xStart + 75;
        newButton.minY = yStart + 20;
        newButton.maxY = yStart + 60;
        
        //Add to correct array
        ButtonsConfirm.Add(newButton);
    }
    
    xStart = Canvas->SizeX / 2 + 20;
    yStart = Canvas->SizeY / 2 - 40;
    
    //Highlighted?
    if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Red;
    else ColorPtr = &LC_Yellow;
    
    //Text
    DrawHUDText(
                VerdanaFont, "No", xStart + 30, yStart + 20,
                *ColorPtr, DefaultFontScale,
                true
                );
    
    if (ButtonsConfirm.Num() < 2)
    {
        FHUDButtonStruct newButton = FHUDButtonStruct();
        newButton.type = BUTTONTYPE_CONFIRM_NO;
        newButton.toolTip = "";
        newButton.minX = xStart;
        newButton.maxX = xStart + 75;
        newButton.minY = yStart + 20;
        newButton.maxY = yStart + 60;
        
        //Add to correct array
        ButtonsConfirm.Add(newButton);
    }
}

void AMyHUD::DrawHealthBar()
{
    DrawHUDText(
                VerdanaFont, "Health", 100, 50,
                FColor_White, DefaultFontScale,
                true
                );
    
    ATankCharacter *MyTank = Cast<ATankCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    
    //Goes from left to right
    float y=100;
    for(int i=0; i<MyTank->health; i++){
        DrawHUDRect( y, 100, healthWidth, 50, FLinearColor(0,1,0,1));
        y+=healthWidth;
    }
    
    
    //DrawHUDRect(100, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    //DrawHUDRect(150, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    //DrawHUDRect(200, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    //DrawHUDRect(250, 100, 50, 50, FLinearColor(0, 1, 0, 1));
    //DrawHUDRect(300, 100, 50, 50, FLinearColor(0, 1, 0, 1));
}

// Is cursor in Buttons
int32 AMyHUD::CheckCursorInButton(const TArray<FHUDButtonStruct>& ButtonArray)
{
    for (int32 b = 0; b < ButtonArray.Num(); b++)
    {
        CurCheckButton = &ButtonArray[b];
        
        //check cursor in bounds
        if (CurCheckButton->minX <= MouseLocation.X && MouseLocation.X <= CurCheckButton->maxX &&
            CurCheckButton->minY <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->maxY)
        {
            
            //Active Button Type
            ActiveButton_Type = CurCheckButton->type;
            
            //Tool Tip
            ActiveButton_Tip = CurCheckButton->toolTip;
            
            //Mouse Clicked?
            if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
            {
                return ActiveButton_Type;
            }
        }
    }
    
    //No Click Occurred This Tick
    return -1;
}

//Check Confirm
void AMyHUD::CheckCursorInButtonsConfirm()
{
    //Check Confirm Buttons
    ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type
    
    if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
    {
        ThePC->ConsoleCommand("Exit");
        return;
    }
    if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
    {
        ConfirmDialogOpen = false;
        ButtonsConfirm.Empty(); //Buttons not needed anymore
        return;
    }
}

//Check Buttons
void AMyHUD::CheckCursorInButtonsMain()
{
    //Check Confirm Buttons
    ClickedButtonType = CheckCursorInButton(ButtonsMain);
    
    if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
    {
        ThePC->ConsoleCommand("RestartLevel");
        return;
    }
    if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
    {
        ConfirmDialogOpen = true;
        return;
    }
}
void AMyHUD::DrawHUD_CheckCursorInButtons()
{
    if (ConfirmDialogOpen)
    {
        CheckCursorInButtonsConfirm();
        
        return;
    }
    
    CheckCursorInButtonsMain();
}

void AMyHUD::DrawToolTip()
{
    float xStart = MouseLocation.X + 150;
    float yStart = MouseLocation.Y + 5;
    
    //out vars
    float RV_xLength;
    float RV_yLength;
    
    //Text Size
    GetTextSize(
                ActiveButton_Tip,
                RV_xLength,
                RV_yLength,
                UE4Font,
                DefaultFontScale
                );
    
    
    if (xStart + RV_xLength >= Canvas->SizeX - 40)
    {
        xStart -= 150 + 140 + 64 + RV_xLength;
        
        if (xStart < 33) xStart = 33;
    }
    
    //Background
    DrawHUDRect(
                xStart, yStart,
                RV_xLength + 70,
                80,
                FLinearColor(0, 0, 1, 0.7) //alpha 0.7
                );
    
    //Tool Tip
    DrawText(
             ActiveButton_Tip,
             LC_Black,
             xStart + 32, yStart + 20,
             UE4Font,
             DefaultFontScale,
             false
             );
}

void AMyHUD::DrawHUD_Reset()
{
    ActiveButton_Type = -1;
    ActiveButton_Tip = "";
    CursorHoveringInButton = false;
}

void AMyHUD::DrawHUD()
{
    ATankCharacter *MyTank = Cast<ATankCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
    
    MainMenuOn = MyTank->MainMenuOn;
    
    if (MyTank->MainMenuOn) {
        
        //Have PC for Mouse Cursor?
        if (!ThePC)
        {
            //Attempt to Reacquire PC
            ThePC = GetOwningPlayerController();
            
            //Could Not Obtain PC
            if (!ThePC) return;
        }
        
        //Display the Cursor
        ThePC->bShowMouseCursor = true;
        
        //Draw HUD?
        if (DontDrawHUD) return;
        
        //Reset States
        DrawHUD_Reset();
        
        //Get New Mouse Position
        ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);
        
        //Cursor In Buttons
        DrawHUD_CheckCursorInButtons();
        
        //Draw Dialogs
        DrawHUD_DrawDialogs();
        if (ActiveButton_Tip != "") DrawToolTip();
        
        
    } else {
        
        //Have PC for Mouse Cursor?
        if (!ThePC)
        {
            //Attempt to Reacquire PC
            ThePC = GetOwningPlayerController();
            
            //Could Not Obtain PC
            if (!ThePC) return;
        }
        
        ThePC->bShowMouseCursor = false;
    }
    
    //Super
    Super::DrawHUD();
    
    //No Canvas?
    if (!Canvas) return;
    
    //Reset States
    //DrawHUD_Reset();
    
    //Get New Mouse Position
    //ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);
    
    //Cursor In Buttons
    //DrawHUD_CheckCursorInButtons();
    
    //Draw Dialogs
    //DrawHUD_DrawDialogs();
    
    DrawHealthBar();
    
    DrawRadar();
    
    //if (ActiveButton_Tip != "") DrawToolTip();
    
    if (MyTank->lost && !won){
        loss = true;
    }
    
    if (!MyTank->lost && !won) {
        checkWin();
    }
}


//  Radar things
//  DrawRadar()
//      Draw the circle the radar will sit on. Call DrawOtherPlayers and DrawRadarSweep.
void AMyHUD::DrawRadar()
{
    //  3 == detail of the circle
    int NumPoints = (int)(pow(2,1+4));
    float radar_scale, radar_range, min;
    FVector2D radar_center;
    //  randomly chosen number, change freely. Woorld coords.
    radar_range = 900.0;
    FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);
    
    //  Radar occupies 1/3 o smaller dimension, perfect circle
    min = (ScreenSize.X < ScreenSize.Y) ? ScreenSize.X:ScreenSize.Y;
    radar_scale = .33 * min * .5;
    radar_center = FVector2D( ScreenSize.X - radar_scale - 15, ScreenSize.Y - radar_scale - 15 );
    
    //  Draw background circle
    Canvas->K2_DrawPolygon(0, radar_center, FVector2D(radar_scale,radar_scale), NumPoints, FColor(94,145,145));
    DrawOtherPlayers(radar_scale, radar_center, radar_range);
    DrawRadarSweep(radar_scale, radar_center);
}


//  DrawOtherPlayers()
//      radar_scale is in screen pixels
//      radar_center is screen coordinate
//      radar_range is world coordinate
//  Draw dots for each nearby "tank"
void AMyHUD::DrawOtherPlayers(float radar_scale, FVector2D radar_center, float radar_range)
{
    if(!GetOwningPawn())
        return;
    FVector2D Me = FVector2D(GetOwningPawn()->GetActorLocation().X, GetOwningPawn()->GetActorLocation().Y);
    FString myName = GetOwningPawn()->GetName();
    FVector2D Them;
    FString theirName;
    FColor lineColor = FColor(204,255,255);
    float LineThickness = 3;
    float diamondLength = 5;
    float rotateByDegree;
    diamondLength = 3;
    //  searching for classes AEnemy, ATankCharacter
    for( FActorIterator ActorItr(GetWorld()) ; ActorItr; ++ActorItr){
        theirName = ActorItr->GetName();
        if( theirName!=myName && theirName.Contains("BP_Enemy", ESearchCase::IgnoreCase, ESearchDir::FromStart) ){
            
            ATankCharacter *owningTank = Cast<ATankCharacter>(GetOwningPawn());
            FVector them3D = ActorItr->GetActorLocation();
            Them = FVector2D(them3D.X, them3D.Y);
            
            //  If the nearby actor is within my radar_range world coordinates
            if( FVector2D::Distance(Me, Them) < radar_range ){
                Them = Them - Me;
                Them = Them / radar_range * radar_scale;
                Them = Them + radar_center;
                
                //  Draw a diamond for them on the minimap
                DrawLine(
                         FVector(Them.X-diamondLength, Them.Y, 0),
                         FVector(Them.X, Them.Y+diamondLength, 0),
                         lineColor, LineThickness);
                DrawLine(
                         FVector(Them.X, Them.Y+diamondLength, 0),
                         FVector(Them.X+diamondLength, Them.Y, 0),
                         lineColor, LineThickness);
                DrawLine(
                         FVector(Them.X+diamondLength, Them.Y, 0),
                         FVector(Them.X, Them.Y-diamondLength, 0),
                         lineColor, LineThickness);
                DrawLine(
                         FVector(Them.X, Them.Y-diamondLength, 0),
                         FVector(Them.X-diamondLength, Them.Y, 0),
                         lineColor, LineThickness);
            }
        }
    }
}
//  DrawRadarSweep()
//      radar_scale is in screen pixels
//      radar_center is screen coordinate
//      radar_range is world coordinate
//  Draw a line that spins around the center (like a clock)
void AMyHUD::DrawRadarSweep(float radar_scale, FVector2D radar_center)
{
    static FVector2D sweeper = FVector2D(0,1) * radar_scale;
    sweeper = RotateVector(sweeper, .025);
    sweeper = sweeper.GetSafeNormal(.03) * radar_scale;
    
    DrawLine(
             FVector(radar_center.X, radar_center.Y, 0),
             FVector(sweeper.X+radar_center.X, sweeper.Y+radar_center.Y, 0),
             FColor(204,255,255),
             1
             );
}
/*  DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick)
 *   Draws a line on the screen from Start to End
 *   The line will be color TheColor, ie. FColor::Red
 *   the float is the thickness of the line (in pixels?)
 */
void AMyHUD::DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick)
{
    FCanvasLineItem NewLine(Start,End);
    NewLine.SetColor(TheColor);
    NewLine.LineThickness = Thick;
    Canvas->DrawItem(NewLine);
}
//  RotateVector(FVector2D, float)
//      Return this vector rotated by these degrees
FVector2D AMyHUD::RotateVector(FVector2D input, float delta)
{
    float newX, newY;
    newX = input.X * cos(delta) - input.Y * sin(delta);
    newY = input.X * sin(delta) + input.Y * cos(delta);
    return FVector2D(newX, newY);
}


/**
 Function called to check if the user has won
 
 - parameter void:
 - returns: void
 */
void AMyHUD::checkWin(){
    bool current = true;
    
    //if there are any enemys left, we haven't won yet
    for( FActorIterator ActorItr(GetWorld()) ; ActorItr; ++ActorItr){
        if (ActorItr->GetName().Contains("BP_Enemy")){
            current = false;
        }
    }
    
    won = current;
}

/**
 Function that prints the current controls that are used in the game

 -parameter void:
 -returns: void
*/
void AMyHUD::DrawInstructions(){
     FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);
    FVector2D WinSize;
    GetTextSize(TEXT("Controls to Move: WASD to change "), WinSize.X, WinSize.Y, VerdanaFont);
    DrawText(TEXT("YAY!! YOU WON!! :D "), FColor::Red, (ScreenSize.X - WinSize.X) / 2.0f, (ScreenSize.Y - WinSize.Y) / 2.0f, VerdanaFont);
}