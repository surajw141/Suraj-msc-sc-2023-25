import FrameComponent3 from "../components/FrameComponent3";
import FrameComponent2 from "../components/FrameComponent2";
import FrameComponent from "../components/FrameComponent";
import "./ServiceProviderRegistration.css";

const ServiceProviderRegistration = () => {
  return (
    <div className="service-provider-registration">
      <FrameComponent3 />
      <div className="store-name-frame" />
      <FrameComponent2 />
      <div className="state-selection" />
      <div className="area-street-shopno">
        <div className="save-and-continue">
          <h3 className="give-your-store">Give your store name</h3>
          <div className="you-can-update">
            You can update the store name at any time from account settings post
            registration
          </div>
        </div>
      </div>
      <img className="arrow-icon" loading="eager" alt="" src="/vector-3.svg" />
      <div className="shipping-preference-frame">
        <form className="your-store-name">
          <FrameComponent />
          <button className="continue-btn">
            <img
              className="continue-btn-child"
              alt=""
              src="/rectangle-29.svg"
            />
            <div className="save-and-continue1">Save and Continue</div>
          </button>
        </form>
      </div>
    </div>
  );
};

export default ServiceProviderRegistration;
