import Button from "./Button";
import "./BackgroundFrame.css";

const BackgroundFrame = () => {
  return (
    <div className="background-frame">
      <div className="background-frame-child" />
      <Button
        oneOfUs="New Here ?"
        ifYouAlreadyHaveAnAccount="sign up and discover a great"
        justSignInWeveMissedYou=" amount of new deal!"
        signIn="Sign Up"
        justSignInPadding="unset"
        propBoxShadow="unset"
        propBoxShadow1="unset"
      />
      <div className="ellipse-parent">
        <div className="ellipse-div" />
        <div className="o-r-symbol" />
        <div className="o-r-symbol1" />
      </div>
    </div>
  );
};

export default BackgroundFrame;
