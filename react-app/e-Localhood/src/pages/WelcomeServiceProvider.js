import "./WelcomeServiceProvider.css";

const WelcomeServiceProvider = () => {
  return (
    <div className="welcome-service-provider">
      <img
        className="image-1-icon"
        loading="eager"
        alt=""
        src="/image-1@2x.png"
      />
      <div className="with-e-localhood-you-container">
        <p className="with-e-localhood-you">
          With e-Localhood, you have flexible working hours and
        </p>
        <p className="help-us-make">help us make deliveries in you city.</p>
      </div>
      <div className="welcome-service-provider-inner">
        <main className="rectangle-parent">
          <div className="frame-child" />
          <div className="e-localhood-label">
            <h1 className="e-localhood1">e-Localhood</h1>
            <h2 className="become-a-service-container">
              <p className="become-a-service">Become a service</p>
              <p className="provider-and"> provider and</p>
              <p className="start-earning"> start earning</p>
            </h2>
          </div>
          <div className="frame-wrapper">
            <button className="rectangle-group">
              <div className="frame-item" />
              <div className="become-a-service1">Become a service provider</div>
            </button>
          </div>
        </main>
      </div>
    </div>
  );
};

export default WelcomeServiceProvider;
