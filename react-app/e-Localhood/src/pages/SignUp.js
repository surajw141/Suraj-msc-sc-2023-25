import FrameComponent4 from "../components/FrameComponent4";
import "./SignUp.css";

const SignUp = () => {
  return (
    <div className="sign-up">
      <FrameComponent4 />
      <div className="sign-up-with" />
      <div className="sign-up-child" />
      <div className="sign-up-item" />
      <div className="sign-up-inner">
        <div className="o-r-parent">
          <div className="o-r">
            <div className="o-r-child" />
            <div className="o-r-item" />
            <div className="o-r-inner" />
          </div>
          <div className="mobile-no">
            <div className="email-input">
              <div className="sign-in-button">
                <h1 className="create-free-account">Create Free Account</h1>
              </div>
              <div className="create-account-label">
                <b className="sign-up-using">Sign up using social networks</b>
              </div>
              <form className="first-last-name-fields">
                <div className="mobile-number-field">
                  <div className="email-field">
                    <div className="password-field">
                      <div className="terms-checkbox" />
                      <b className="f1">f</b>
                    </div>
                    <div className="password-field1">
                      <div className="password-field-child" />
                      <b className="g1">G+</b>
                    </div>
                    <div className="password-field2">
                      <div className="password-field-item" />
                      <b className="y1">Y</b>
                    </div>
                  </div>
                  <div className="o-r-text-parent">
                    <div className="o-r-text" />
                    <b className="or1">OR</b>
                    <div className="o-r-text1" />
                  </div>
                </div>
                <div className="contact-info-fields">
                  <div className="main-form">
                    <input
                      className="input-field-group"
                      placeholder={`First & Last Name`}
                      type="text"
                    />
                    <input
                      className="register-button"
                      placeholder="Mobile no"
                      type="text"
                    />
                  </div>
                  <div className="main-form1">
                    <div className="rectangle-parent2">
                      <div className="frame-child7" />
                      <b className="email">Email</b>
                    </div>
                    <input
                      className="main-form-child"
                      placeholder="Password"
                      type="text"
                    />
                  </div>
                </div>
                <div className="sign-up-confirmation-message">
                  <input className="confirmation-frame1" type="checkbox" />
                  <b className="i-have-read">{`I have read the Term & Conditions`}</b>
                </div>
                <div className="input-fields">
                  <button className="submit-btn">
                    <div className="submit-btn-child" />
                    <b className="sign-up1">Sign up</b>
                  </button>
                </div>
              </form>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default SignUp;
