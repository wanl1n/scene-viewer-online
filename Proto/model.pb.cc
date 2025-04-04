// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: model.proto
// Protobuf C++ Version: 5.29.3

#include "model.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;

inline constexpr ModelResponse::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : modeldata_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ModelResponse::ModelResponse(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ModelResponseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ModelResponseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ModelResponseDefaultTypeInternal() {}
  union {
    ModelResponse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ModelResponseDefaultTypeInternal _ModelResponse_default_instance_;

inline constexpr ModelRequest::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : modelname_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR ModelRequest::ModelRequest(::_pbi::ConstantInitialized)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(_class_data_.base()),
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(),
#endif  // PROTOBUF_CUSTOM_VTABLE
      _impl_(::_pbi::ConstantInitialized()) {
}
struct ModelRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ModelRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~ModelRequestDefaultTypeInternal() {}
  union {
    ModelRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ModelRequestDefaultTypeInternal _ModelRequest_default_instance_;
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_model_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_model_2eproto = nullptr;
const ::uint32_t
    TableStruct_model_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::ModelRequest, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::ModelRequest, _impl_.modelname_),
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::ModelResponse, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::ModelResponse, _impl_.modeldata_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::ModelRequest)},
        {9, -1, -1, sizeof(::ModelResponse)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::_ModelRequest_default_instance_._instance,
    &::_ModelResponse_default_instance_._instance,
};
const char descriptor_table_protodef_model_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\013model.proto\"!\n\014ModelRequest\022\021\n\tmodelNa"
    "me\030\001 \001(\t\"\"\n\rModelResponse\022\021\n\tmodelData\030\001"
    " \001(\t2<\n\013ModelLoader\022-\n\010GetModel\022\r.ModelR"
    "equest\032\016.ModelResponse\"\0000\001b\006proto3"
};
static ::absl::once_flag descriptor_table_model_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_model_2eproto = {
    false,
    false,
    154,
    descriptor_table_protodef_model_2eproto,
    "model.proto",
    &descriptor_table_model_2eproto_once,
    nullptr,
    0,
    2,
    schemas,
    file_default_instances,
    TableStruct_model_2eproto::offsets,
    file_level_enum_descriptors_model_2eproto,
    file_level_service_descriptors_model_2eproto,
};
// ===================================================================

class ModelRequest::_Internal {
 public:
};

ModelRequest::ModelRequest(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ModelRequest)
}
inline PROTOBUF_NDEBUG_INLINE ModelRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::ModelRequest& from_msg)
      : modelname_(arena, from.modelname_),
        _cached_size_{0} {}

ModelRequest::ModelRequest(
    ::google::protobuf::Arena* arena,
    const ModelRequest& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ModelRequest* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:ModelRequest)
}
inline PROTOBUF_NDEBUG_INLINE ModelRequest::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : modelname_(arena),
        _cached_size_{0} {}

inline void ModelRequest::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
ModelRequest::~ModelRequest() {
  // @@protoc_insertion_point(destructor:ModelRequest)
  SharedDtor(*this);
}
inline void ModelRequest::SharedDtor(MessageLite& self) {
  ModelRequest& this_ = static_cast<ModelRequest&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.modelname_.Destroy();
  this_._impl_.~Impl_();
}

inline void* ModelRequest::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) ModelRequest(arena);
}
constexpr auto ModelRequest::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(ModelRequest),
                                            alignof(ModelRequest));
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull ModelRequest::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_ModelRequest_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &ModelRequest::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<ModelRequest>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &ModelRequest::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<ModelRequest>(), &ModelRequest::ByteSizeLong,
            &ModelRequest::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(ModelRequest, _impl_._cached_size_),
        false,
    },
    &ModelRequest::kDescriptorMethods,
    &descriptor_table_model_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* ModelRequest::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 30, 2> ModelRequest::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::ModelRequest>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string modelName = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(ModelRequest, _impl_.modelname_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string modelName = 1;
    {PROTOBUF_FIELD_OFFSET(ModelRequest, _impl_.modelname_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\14\11\0\0\0\0\0\0"
    "ModelRequest"
    "modelName"
  }},
};

PROTOBUF_NOINLINE void ModelRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:ModelRequest)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.modelname_.ClearToEmpty();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* ModelRequest::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const ModelRequest& this_ = static_cast<const ModelRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* ModelRequest::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const ModelRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:ModelRequest)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // string modelName = 1;
          if (!this_._internal_modelname().empty()) {
            const std::string& _s = this_._internal_modelname();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ModelRequest.modelName");
            target = stream->WriteStringMaybeAliased(1, _s, target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:ModelRequest)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t ModelRequest::ByteSizeLong(const MessageLite& base) {
          const ModelRequest& this_ = static_cast<const ModelRequest&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t ModelRequest::ByteSizeLong() const {
          const ModelRequest& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:ModelRequest)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

           {
            // string modelName = 1;
            if (!this_._internal_modelname().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_modelname());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void ModelRequest::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<ModelRequest*>(&to_msg);
  auto& from = static_cast<const ModelRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ModelRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_modelname().empty()) {
    _this->_internal_set_modelname(from._internal_modelname());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void ModelRequest::CopyFrom(const ModelRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ModelRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void ModelRequest::InternalSwap(ModelRequest* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.modelname_, &other->_impl_.modelname_, arena);
}

::google::protobuf::Metadata ModelRequest::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class ModelResponse::_Internal {
 public:
};

ModelResponse::ModelResponse(::google::protobuf::Arena* arena)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ModelResponse)
}
inline PROTOBUF_NDEBUG_INLINE ModelResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::ModelResponse& from_msg)
      : modeldata_(arena, from.modeldata_),
        _cached_size_{0} {}

ModelResponse::ModelResponse(
    ::google::protobuf::Arena* arena,
    const ModelResponse& from)
#if defined(PROTOBUF_CUSTOM_VTABLE)
    : ::google::protobuf::Message(arena, _class_data_.base()) {
#else   // PROTOBUF_CUSTOM_VTABLE
    : ::google::protobuf::Message(arena) {
#endif  // PROTOBUF_CUSTOM_VTABLE
  ModelResponse* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);

  // @@protoc_insertion_point(copy_constructor:ModelResponse)
}
inline PROTOBUF_NDEBUG_INLINE ModelResponse::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : modeldata_(arena),
        _cached_size_{0} {}

inline void ModelResponse::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
ModelResponse::~ModelResponse() {
  // @@protoc_insertion_point(destructor:ModelResponse)
  SharedDtor(*this);
}
inline void ModelResponse::SharedDtor(MessageLite& self) {
  ModelResponse& this_ = static_cast<ModelResponse&>(self);
  this_._internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  ABSL_DCHECK(this_.GetArena() == nullptr);
  this_._impl_.modeldata_.Destroy();
  this_._impl_.~Impl_();
}

inline void* ModelResponse::PlacementNew_(const void*, void* mem,
                                        ::google::protobuf::Arena* arena) {
  return ::new (mem) ModelResponse(arena);
}
constexpr auto ModelResponse::InternalNewImpl_() {
  return ::google::protobuf::internal::MessageCreator::CopyInit(sizeof(ModelResponse),
                                            alignof(ModelResponse));
}
PROTOBUF_CONSTINIT
PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::google::protobuf::internal::ClassDataFull ModelResponse::_class_data_ = {
    ::google::protobuf::internal::ClassData{
        &_ModelResponse_default_instance_._instance,
        &_table_.header,
        nullptr,  // OnDemandRegisterArenaDtor
        nullptr,  // IsInitialized
        &ModelResponse::MergeImpl,
        ::google::protobuf::Message::GetNewImpl<ModelResponse>(),
#if defined(PROTOBUF_CUSTOM_VTABLE)
        &ModelResponse::SharedDtor,
        ::google::protobuf::Message::GetClearImpl<ModelResponse>(), &ModelResponse::ByteSizeLong,
            &ModelResponse::_InternalSerialize,
#endif  // PROTOBUF_CUSTOM_VTABLE
        PROTOBUF_FIELD_OFFSET(ModelResponse, _impl_._cached_size_),
        false,
    },
    &ModelResponse::kDescriptorMethods,
    &descriptor_table_model_2eproto,
    nullptr,  // tracker
};
const ::google::protobuf::internal::ClassData* ModelResponse::GetClassData() const {
  ::google::protobuf::internal::PrefetchToLocalCache(&_class_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_class_data_.tc_table);
  return _class_data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 31, 2> ModelResponse::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    _class_data_.base(),
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::ModelResponse>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string modelData = 1;
    {::_pbi::TcParser::FastUS1,
     {10, 63, 0, PROTOBUF_FIELD_OFFSET(ModelResponse, _impl_.modeldata_)}},
  }}, {{
    65535, 65535
  }}, {{
    // string modelData = 1;
    {PROTOBUF_FIELD_OFFSET(ModelResponse, _impl_.modeldata_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\15\11\0\0\0\0\0\0"
    "ModelResponse"
    "modelData"
  }},
};

PROTOBUF_NOINLINE void ModelResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:ModelResponse)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.modeldata_.ClearToEmpty();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::uint8_t* ModelResponse::_InternalSerialize(
            const MessageLite& base, ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) {
          const ModelResponse& this_ = static_cast<const ModelResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::uint8_t* ModelResponse::_InternalSerialize(
            ::uint8_t* target,
            ::google::protobuf::io::EpsCopyOutputStream* stream) const {
          const ModelResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(serialize_to_array_start:ModelResponse)
          ::uint32_t cached_has_bits = 0;
          (void)cached_has_bits;

          // string modelData = 1;
          if (!this_._internal_modeldata().empty()) {
            const std::string& _s = this_._internal_modeldata();
            ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
                _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "ModelResponse.modelData");
            target = stream->WriteStringMaybeAliased(1, _s, target);
          }

          if (PROTOBUF_PREDICT_FALSE(this_._internal_metadata_.have_unknown_fields())) {
            target =
                ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
                    this_._internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
          }
          // @@protoc_insertion_point(serialize_to_array_end:ModelResponse)
          return target;
        }

#if defined(PROTOBUF_CUSTOM_VTABLE)
        ::size_t ModelResponse::ByteSizeLong(const MessageLite& base) {
          const ModelResponse& this_ = static_cast<const ModelResponse&>(base);
#else   // PROTOBUF_CUSTOM_VTABLE
        ::size_t ModelResponse::ByteSizeLong() const {
          const ModelResponse& this_ = *this;
#endif  // PROTOBUF_CUSTOM_VTABLE
          // @@protoc_insertion_point(message_byte_size_start:ModelResponse)
          ::size_t total_size = 0;

          ::uint32_t cached_has_bits = 0;
          // Prevent compiler warnings about cached_has_bits being unused
          (void)cached_has_bits;

           {
            // string modelData = 1;
            if (!this_._internal_modeldata().empty()) {
              total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                              this_._internal_modeldata());
            }
          }
          return this_.MaybeComputeUnknownFieldsSize(total_size,
                                                     &this_._impl_._cached_size_);
        }

void ModelResponse::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<ModelResponse*>(&to_msg);
  auto& from = static_cast<const ModelResponse&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ModelResponse)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_modeldata().empty()) {
    _this->_internal_set_modeldata(from._internal_modeldata());
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void ModelResponse::CopyFrom(const ModelResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ModelResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void ModelResponse::InternalSwap(ModelResponse* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.modeldata_, &other->_impl_.modeldata_, arena);
}

::google::protobuf::Metadata ModelResponse::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_model_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
