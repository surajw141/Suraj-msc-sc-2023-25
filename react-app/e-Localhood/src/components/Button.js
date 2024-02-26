import { useMemo } from "react";
import "./Button.css";

const Button = ({
  oneOfUs,
  ifYouAlreadyHaveAnAccount,
  justSignInWeveMissedYou,
  signIn,
  justSignInPadding,
  propBoxShadow,
  propBoxShadow1,
}) => {
  const buttonStyle = useMemo(() => {
    return {
      padding: justSignInPadding,
    };
  }, [justSignInPadding]);

  const ellipseStyle = useMemo(() => {
    return {
      boxShadow: propBoxShadow,
    };
  }, [propBoxShadow]);

  const rectangleDivStyle = useMemo(() => {
    return {
      boxShadow: propBoxShadow1,
    };
  }, [propBoxShadow1]);

  return (
    <div className="button" style={buttonStyle}>
      <div className="one-of-us-parent">
        <div className="one-of-us">
          <h1 className="one-of-us1">{oneOfUs}</h1>
        </div>
        <h2 className="if-you-already-container">
          <p className="if-you-already">{ifYouAlreadyHaveAnAccount}</p>
          <p className="just-sign-in">{justSignInWeveMissedYou}</p>
        </h2>
      </div>
      <button className="ellipse" style={ellipseStyle}>
        <div className="ellipse-child" style={rectangleDivStyle} />
        <b className="sign-in">{signIn}</b>
      </button>
    </div>
  );
};

export default Button;
