import Button from "./Button";
import "./FrameComponent4.css";

const FrameComponent4 = () => {
  return (
    <div className="rectangle-parent3">
      <div className="frame-child8" />
      <div className="text-input-wrapper">
        <button className="text-input">
          <div className="text-input-child" />
          <b className="e-localhood4">e-Localhood</b>
        </button>
      </div>
      <Button
        oneOfUs="One Of Us ?"
        ifYouAlreadyHaveAnAccount="If you already have an account,"
        justSignInWeveMissedYou=" just sign in. We've missed you!"
        signIn="Sign in"
      />
    </div>
  );
};

export default FrameComponent4;
