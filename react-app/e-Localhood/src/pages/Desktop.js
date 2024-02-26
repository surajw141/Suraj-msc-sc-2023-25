import "./Desktop.css";

const Desktop = () => {
  return (
    <div className="desktop-1">
      <div className="rectangle-container">
        <div className="rectangle-div" />
        <div className="e-localhood-wrapper">
          <h3 className="e-localhood2">e-Localhood</h3>
        </div>
        <div className="confirmation-frame">
          <h2 className="registration-complete">Registration complete!</h2>
          <b className="congratulations-you-are">{`Congratulations! You are now an e-Localhood Service provider.  `}</b>
        </div>
        <div className="add-services-frame">
          <div className="frame-div">
            <div className="frame-child5" />
            <div className="your-service-provider">
              YOUR SERVICE PROVIDER ID
            </div>
            <b className="s-f-d">S F D 1 S F D 5 D 1 1</b>
            <button className="rectangle-parent1">
              <div className="frame-child6" />
              <b className="abk-electricals-">ABK electricals - MH</b>
            </button>
          </div>
        </div>
        <button className="registration-complete-frame">
          <img
            className="registration-complete-frame-child"
            alt=""
            src="/rectangle-29.svg"
          />
          <div className="add-services-and">Add services and start selling</div>
        </button>
      </div>
    </div>
  );
};

export default Desktop;
