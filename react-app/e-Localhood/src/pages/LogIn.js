import BackgroundFrame from "../components/BackgroundFrame";
import "./LogIn.css";

const LogIn = () => {
  return (
    <div className="log-in">
      <div className="frame-login">
        <div className="frame-content">
          <header className="framee-localhood">
            <div className="framee-localhood-child" />
            <h2 className="e-localhood">e-Localhood</h2>
          </header>
          <div className="frame-social-login">
            <form className="frame-email-mobile">
              <h1 className="login-to-your">Login to Your Account</h1>
              <div className="frame-button">
                <b className="login-using-social">
                  Login using social networks
                </b>
                <div className="frame-input-group">
                  <div className="input-password">
                    <div className="frames-loading-ellipse">
                      <div className="ellipse-a" />
                      <b className="f">f</b>
                    </div>
                    <div className="frames-loading-ellipse1">
                      <div className="frames-loading-ellipse-child" />
                      <b className="g">G+</b>
                    </div>
                    <div className="frames-loading-ellipse2">
                      <div className="frames-loading-ellipse-item" />
                      <b className="y">Y</b>
                    </div>
                  </div>
                  <div className="frame-o-r">
                    <div className="rectangle-divider" />
                    <b className="or">OR</b>
                    <div className="rectangle-divider1" />
                  </div>
                  <input
                    className="frame-email-mobile-input"
                    placeholder="Email /Mobile no"
                    type="text"
                  />
                  <input
                    className="frame-email-mobile-input1"
                    placeholder="Password"
                    type="text"
                  />
                </div>
              </div>
              <div className="signup-container">
                <button className="login-button">
                  <div className="login-button-child" />
                  <b className="signin">Signin</b>
                </button>
              </div>
            </form>
          </div>
        </div>
      </div>
      <BackgroundFrame />
    </div>
  );
};

export default LogIn;
