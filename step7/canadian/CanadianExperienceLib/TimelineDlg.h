/**
 * @file TimelineDlg.h
 * @author Cameron Schwindaman
 *
 * Timeline dialog box
 */
 
#ifndef TIMELINEDLG_H
#define TIMELINEDLG_H

class Timeline;

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// The animation timeline
    Timeline* mTimeline;

    /// Number of frames in the animation
    int mNumberOfFrames;

    /// The number of frames per second
    int mFrameRate;

public:
    TimelineDlg(wxWindow* parent, Timeline* timeline);
    void OnOK(wxCommandEvent& event);
};

#endif //TIMELINEDLG_H